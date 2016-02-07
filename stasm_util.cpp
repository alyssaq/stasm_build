// command line utility to run stasm on an image
// Alyssa Quek 2015

#include <stdio.h>
#include <stdlib.h>
#include "opencv/highgui.h"
#include "stasm.h"

namespace stasm {
static int  showimg_g = false;                // -s flag
static bool csv_g;                            // -c flag
static const char* datafolder_g;
//-----------------------------------------------------------------------------
static void GetOptions(int &argc, const char** &argv) {
  static const char* const usage =
    "./stasm_util [FLAGS] <image_path>\n"
    "\n"
    "Prints 77 (x, y) landmarks to terminal\n"
    "\n"
    "Example: ./stasm_util -f data face.jpg\n"
    "\n"
    "Flags:\n"
    "    -f     folder to xml data\n"
    "    -s     show image with landmarks\n"
    "    -?     help\n"
    "\n";

  if (argc < 2) {
    Err("No image.  Use stasm -? for help.");
  }
  while (--argc > 0 && (*++argv)[0] == '-') {
    if ((*argv + 1)[1]) {
      Err("Invalid argument -%s (there must be a space after -%c).  "
        "Use stasm -? for help.",
        *argv + 1, (*argv + 1)[0]);
    }
    switch ((*argv + 1)[0]) {
    case 's':
      showimg_g = true;
      break;
    case 'f':
      if (argc < 3)
        Err("-f argument must be followed by folder path.  For example -f data/");
      argc--;
      argv++;
      datafolder_g = *argv;
      break;
    case '?':
      printf("%s", usage);
      exit(1);
    default:
      Err("Invalid argument -%s.  Use stasm -? for help.", *argv + 1);
      break;
    }
  }
  if (argc < 1) {
    Err("No image.  Use stasm -? for help.");
  }
}

static void ProcessImg(const char* imgpath) {
  cv::Mat_<unsigned char> img(cv::imread(imgpath, CV_LOAD_IMAGE_GRAYSCALE));

  if (!img.data) {
    printf("Cannot load %s\n", imgpath);
    exit(1);
  }

  int foundface;
  float landmarks[2 * stasm_NLANDMARKS]; // x,y coords (note the 2)

  if (!stasm_search_single(&foundface, landmarks,
      (const char*) img.data, img.cols, img.rows, imgpath, datafolder_g)) {
    printf("Error in stasm_search_single: %s\n", stasm_lasterr());
    exit(1);
  }

  if (!foundface) {
    printf("No face found in %s\n", imgpath);
  } else {
    // draw the landmarks on the image as white dots (image is monochrome)
    stasm_force_points_into_image(landmarks, img.cols, img.rows);
    // printf("Num points: %d \n", stasm_NLANDMARKS);
    for (int i = 0; i < stasm_NLANDMARKS; i++) {
      printf("%d %d\n", cvRound(landmarks[i*2]), cvRound(landmarks[i*2+1]));
      if (showimg_g) {
        img(cvRound(landmarks[i*2+1]), cvRound(landmarks[i*2])) = 255;
      }
    }
  }

  if (showimg_g) {
    cv::imshow("stasm face points", img);
    cv::waitKey();
  }
}

static void main(int argc, const char** argv) {
  GetOptions(argc, argv);

  // argc is now the number of images and argv is the image filenames
  if (!stasm_init(datafolder_g, 0 /*trace*/)) {
    Err("stasm_init failed %s", stasm_lasterr());
  }

  for (int i_img = 0; i_img < argc; i_img++) {
    const char* const imgpath = argv[i_img];
    ProcessImg(imgpath);
  }
}

} // namespace stasm

int main(int argc, const char** argv) {
  stasm::CatchOpenCvErrs();
  try {
    stasm::main(argc, argv);
  } catch(...) {
    // a call was made to Err or a CV_Assert failed
    printf("\n%s\n", stasm_lasterr());
    exit(1);
  }
  return 0; // success
}
