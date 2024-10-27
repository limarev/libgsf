#include <gsf-config.h>
#include <gsf/gsf.h>
#include <glib/gi18n.h>
#include <glib/gstdio.h>
#include <gio/gio.h>
#include <locale.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

struct Stream {
  std::u16string path;
  std::vector<uint8_t> content;
};

using Streams = std::vector<Stream>;

static void
show_error (char const *name, GError *error)
{
  char *display_name;
  display_name = g_filename_display_name (name);
  g_printerr (_("%s: Error processing file %s: %s\n"),
        g_get_prgname (),
        display_name,
        error->message);
  g_free (display_name);
}

/* Walks "path" directory structure while loading it in "outfile" */
static void
load_recursively (GsfOutfile *outfile, char const *path)
{
  std::cout << path << std::endl;
  GError *error = NULL;
  GStatBuf statbuf;

  if (g_stat (path, &statbuf) == -1) {
    g_printerr ("Failed to stat %s: %s\n",
          path, g_strerror (errno));
    return;
  }

  if (S_ISDIR (statbuf.st_mode)) {
    GsfInfile *in = gsf_infile_stdio_new (path, &error);
    GsfOutfile *out;
    int i, n;
    char *base;

    if (!in) {
      show_error (path, error);
      return;
    }

    base = g_path_get_basename (path);
    out = GSF_OUTFILE (gsf_outfile_new_child (outfile, base, TRUE));
    g_free (base);

    n = gsf_infile_num_children (in);
    for (i = 0; i < n; i++) {
      char const *child = gsf_infile_name_by_index (in, i);
      char *name = g_build_filename (path, child, NULL);
      load_recursively (out, name);
      g_free (name);
    }

    g_object_unref (out);
    g_object_unref (in);
  } else if (S_ISREG (statbuf.st_mode)) {
    char *base;
    GsfInput *in;
    GsfOutput *out;
    gboolean ok;

    in = gsf_input_stdio_new (path, &error);
    if (!in) {
      show_error (path, error);
      return;
    }

    base = g_path_get_basename (path);
    out = gsf_outfile_new_child_full
      (outfile, base, FALSE,
       "modtime", gsf_input_get_modtime (in),
       NULL);
    g_printerr ("Adding %s\n", path);

    ok = gsf_input_copy (in, out);
    if (!ok)
      g_printerr ("Error in adding member.\n");

    ok = gsf_output_close (out);
    if (!ok)
      g_printerr ("Error in adding member (at close)\n");

    g_object_unref (out);
    g_free (base);


    g_object_unref (in);
  } else {
    g_printerr ("Ignoring %s\n", path);
  }
}

static int
gsf_create (const Streams& streams)
{
  GError *error = NULL;
  GsfOutput *dest;
  GsfOutfile *outfile;
  gboolean ok;

  dest = gsf_output_memory_new();
  outfile = gsf_outfile_msole_new (dest);


  for (const auto &[path_, content] : streams) {
    const auto path = reinterpret_cast<const char*>(std::data(path_));
    load_recursively (outfile, path);
  }

  std::vector<uint8_t> content;
  content.reserve(dest->cur_size);
  std::cout << "size: " << dest->cur_size << std::endl;

  auto data = reinterpret_cast<const char*>(gsf_output_memory_get_bytes (GSF_OUTPUT_MEMORY (dest)));
  if (!data) return -1;

  while (*data != '\0') {
    content.push_back(*data);
    // std::cout << *data;
  }
  std::cout << "asd\n";

  const std::filesystem::path output_file_path {"asd.bin"};
  std::ofstream output_file {output_file_path};
  std::ranges::copy (content, std::ostreambuf_iterator<char> (output_file));

  ok = gsf_output_close (GSF_OUTPUT (outfile));
  if (!ok)
    g_printerr ("Error while closing archive\n");

  g_object_unref (dest);
  g_object_unref (outfile);
  return 0;
}

int main() {
  std::string tmp {"asdaskdjaslkjd"};
  std::vector<uint8_t> data {std::begin(tmp), std::end(tmp)};
  Streams streams{{u"dir1/dir2/file", data}};
  gsf_create(streams);
}