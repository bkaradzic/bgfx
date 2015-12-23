# Tiny OpenEXR image library.

![Example](https://github.com/syoyo/tinyexr/blob/master/asakusa.png?raw=true)

[![AppVeyor build status](https://ci.appveyor.com/api/projects/status/k07ftfe4ph057qau/branch/master?svg=true)](https://ci.appveyor.com/project/syoyo/tinyexr/branch/master)

[![Travis build Status](https://travis-ci.org/syoyo/tinyexr.svg)](https://travis-ci.org/syoyo/tinyexr)

[![Coverity Scan Build Status](https://scan.coverity.com/projects/5827/badge.svg)](https://scan.coverity.com/projects/5827)

`tinyexr` is a small, single header-only library to load and save OpenEXR(.exr) images.
`tinyexr` is written in portable C++(no library dependency except for STL), thus `tinyexr` is good to embed into your application.
To use `tinyexr`, simply copy `tinyexr.h` into your project.

`tinyexr` currently supports:

* OpenEXR version 1.x.
* Normal image
  * Scanline format.
  * Uncompress("compress" = 0), ZIPS("compress" = 2), ZIP compression("compress" = 3) and PIZ compression("compress" = 4).
  * Half/Uint/Float pixel type.
  * Custom attributes(up to 128)
* Deep image
  * Scanline format.
  * ZIPS compression("compress" = 2).
  * Half, float pixel type.
* Litte endian machine.
* Limited support for big endian machine.
  * read/write normal image.
* C interface.
  * You can easily write language bindings(e.g. golang)
* EXR saving
  * with ZIP compression.
* JavaScript library
  * Through emscripten.

# Use case 

* mallie https://github.com/lighttransport/mallie
* PBRT v3 https://github.com/mmp/pbrt-v3
* Cinder 0.9.0 https://libcinder.org/notes/v0.9.0
* Piccante(develop branch) http://piccantelib.net/
* Your project here!

## Examples

* [examples/deepview/](examples/deepview) Deep image view
* [examples/rgbe2exr/](examples/rgbe2exr) .hdr to EXR converter
* [examples/exr2rgbe/](examples/exr2rgbe) EXR to .hdr converter

## Usage

NOTE: **API is still subject to change**. See the source code for details.

Include `tinyexr.h` with `TINYEXR_IMPLEMENTATION` flag(do this only for **one** .cc file).

```
#define TINYEXR_IMPLEMENTATION
#include "tinyexr.h"
```

Quickly reading RGB(A) EXR file.

```
  const char* input = "asakusa.exr";
  float* out; // width * height * RGBA
  int width;
  int height;
  const char* err;

  int ret = LoadEXR(&out, &width, &height, input, &err);
```

Loading EXR from a file.

```
  const char* input = "asakusa.exr";
  const char* err;

  EXRImage exrImage;
  InitEXRImage(&exrImage);

  int ret = ParseMultiChannelEXRHeaderFromFile(&exrImage, input, &err);
  if (ret != 0) {
    fprintf(stderr, "Parse EXR err: %s\n", err);
    return;
  }

  //// Uncomment if you want reading HALF image as FLOAT.
  //for (int i = 0; i < exrImage.num_channels; i++) {
  //  if (exrImage.pixel_types[i] = TINYEXR_PIXELTYPE_HALF) {
  //    exrImage.requested_pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT;
  //  }
  //}

  ret = LoadMultiChannelEXRFromFile(&exrImage, input, &err);
  if (ret != 0) {
    fprintf(stderr, "Load EXR err: %s\n", err);
    return;
  }
```

Saving EXR file.

```
  bool SaveEXR(const float* rgb, int width, int height, const char* outfilename) {

    float* channels[3];

    EXRImage image;
    InitEXRImage(&image);

    image.num_channels = 3;

    // Must be BGR(A) order, since most of EXR viewers expect this channel order.
    const char* channel_names[] = {"B", "G", "R"}; // "B", "G", "R", "A" for RGBA image

    std::vector<float> images[3];
    images[0].resize(width * height);
    images[1].resize(width * height);
    images[2].resize(width * height);

    for (int i = 0; i < width * height; i++) {
      images[0][i] = rgb[3*i+0];
      images[1][i] = rgb[3*i+1];
      images[2][i] = rgb[3*i+2];
    }

    float* image_ptr[3];
    image_ptr[0] = &(images[2].at(0)); // B
    image_ptr[1] = &(images[1].at(0)); // G
    image_ptr[2] = &(images[0].at(0)); // R

    image.channel_names = channel_names;
    image.images = (unsigned char**)image_ptr;
    image.width = width;
    image.height = height;
    image.compression = TINYEXR_COMPRESSIONTYPE_ZIP;

    image.pixel_types = (int *)malloc(sizeof(int) * image.num_channels);
    image.requested_pixel_types = (int *)malloc(sizeof(int) * image.num_channels);
    for (int i = 0; i < image.num_channels; i++) {
      image.pixel_types[i] = TINYEXR_PIXELTYPE_FLOAT; // pixel type of input image
      image.requested_pixel_types[i] = TINYEXR_PIXELTYPE_HALF; // pixel type of output image to be stored in .EXR
    }

    const char* err;
    int ret = SaveMultiChannelEXRToFile(&image, outfilename, &err);
    if (ret != 0) {
      fprintf(stderr, "Save EXR err: %s\n", err);
      return ret;
    }
    printf("Saved exr file. [ %s ] \n", outfilename);

    free(image.pixel_types);
    free(image.requested_pixel_types);

    return ret;

  }
```


Reading deep image EXR file.
See `example/deepview` for actual usage.

```
  const char* input = "deepimage.exr";
  const char* err;
  DeepImage deepImage;

  int ret = LoadDeepEXR(&deepImage, input, &err);

  // acccess to each sample in the deep pixel.
  for (int y = 0; y < deepImage.height; y++) {
    int sampleNum = deepImage.offset_table[y][deepImage.width-1];
    for (int x = 0; x < deepImage.width-1; x++) {
      int s_start = deepImage.offset_table[y][x];
      int s_end   = deepImage.offset_table[y][x+1];
      if (s_start >= sampleNum) {
        continue;
      }
      s_end = (s_end < sampleNum) ? s_end : sampleNum;
      for (int s = s_start; s < s_end; s++) {
        float val = deepImage.image[depthChan][y][s];
        ...
      }
    }
  }

```

### deepview

`examples/deepview` is simple deep image viewer in OpenGL.

![DeepViewExample](https://github.com/syoyo/tinyexr/blob/master/examples/deepview/deepview_screencast.gif?raw=true)

## TODO

Contribution is welcome!

- [ ] Compression
  - [ ] NONE("compress" = 0, load)
  - [ ] RLE("compress" = 1, load)
  - [x] ZIPS("compress" = 2, load)
  - [x] ZIP("compress" = 3, load)
  - [x] PIZ("compress" = 4, load)
  - [x] NONE("compress" = 0, save)
  - [ ] RLE("compress" = 1, save)
  - [x] ZIPS("compress" = 2, save)
  - [x] ZIP("compress" = 3, save)
  - [ ] PIZ("compress" = 4, save)
- [ ] Custom attributes
  - [x] Normal image(EXR 1.x)
  - [ ] Deep image(EXR 2.x)
- [ ] JavaScript library
  - [x] LoadEXRFromMemory
  - [ ] SaveMultiChannelEXR
  - [ ] Deep image save/load
- [ ] Write from/to memory buffer.
  - [x] SaveMultiChannelEXR
  - [x] LoadMultiChannelEXR
  - [ ] Deep image save/load
- [ ] Tile format.
- [ ] Support for various compression type.
  - [x] zstd compression(Not in OpenEXR spec, though)
- [x] Multi-channel.
- [ ] Multi-part(EXR2.0)
- [ ] Line order.
  - [x] Increasing, decreasing(load)
  - [ ] Random?
  - [ ] Increasing, decreasing(save)
- [ ] Pixel format(UINT, FLOAT).
  - [x] UINT, FLOAT(load)
  - [x] UINT, FLOAT(deep load)
  - [x] UINT, FLOAT(save)
  - [ ] UINT, FLOAT(deep save)
- [ ] Full support for big endian machine.
  - [x] Loading multi channel EXR
  - [x] Saving multi channel EXR
  - [ ] Loading deep image
  - [ ] Saving deep image
- [ ] Optimization
  - [ ] ISPC?
  - [x] OpenMP multi-threading in EXR loading.
  - [x] OpenMP multi-threading in EXR saving.
  - [ ] OpenMP multi-threading in deep image loading.
  - [ ] OpenMP multi-threading in deep image saving.

## Similar or related projects

* miniexr: https://github.com/aras-p/miniexr (Write OpenEXR)
* stb_image_resize.h: https://github.com/nothings/stb (Good for HDR image resizing)

## License

3-clause BSD

`tinyexr` uses miniz, which is developed by Rich Geldreich <richgel99@gmail.com>, and licensed under public domain.

`tinyexr` tools uses stb, which is licensed under public domain: https://github.com/nothings/stb
`tinyexr` uses some code from OpenEXR, which is licensed under 3-clause BSD license.

## Author(s)

Syoyo Fujita(syoyo@lighttransport.com)

## Contributor(s)

* Matt Ebb (http://mattebb.com) : deep image example. Thanks!
* Matt Pharr (http://pharr.org/matt/) : Testing tinyexr with OpenEXR(IlmImf). Thanks! 
* Andrew Bell (https://github.com/andrewfb) & Richard Eakin (https://github.com/richardeakin) : Improving TinyEXR API. Thanks!
* Mike Wong (https://github.com/mwkm) : ZIPS compression support in loading. Thanks!
