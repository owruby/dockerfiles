// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

  This example program shows how to find frontal human faces in an image and
  estimate their pose.  The pose takes the form of 68 landmarks.  These are
  points on the face such as the corners of the mouth, along the eyebrows, on
  the eyes, and so forth.  
    


  This face detector is made using the classic Histogram of Oriented
  Gradients (HOG) feature combined with a linear classifier, an image pyramid,
  and sliding window detection scheme.  The pose estimator was created by
  using dlib's implementation of the paper:
  One Millisecond Face Alignment with an Ensemble of Regression Trees by
  Vahid Kazemi and Josephine Sullivan, CVPR 2014
  and was trained on the iBUG 300-W face landmark dataset.  

  Also, note that you can train your own models using dlib's machine learning
  tools.  See train_shape_predictor_ex.cpp to see an example.

    


  Finally, note that the face detector is fastest when compiled with at least
  SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
  chip then you should enable at least SSE2 instructions.  If you are using
  cmake to compile this program you can enable them by using one of the
  following commands when you create the build project:
  cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
  cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
  cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
  This will set the appropriate compiler options for GCC, clang, Visual
  Studio, or the Intel compiler.  If you are using another compiler then you
  need to consult your compiler's manual to determine how to enable these
  instructions.  Note that AVX is the fastest but requires a CPU from at least
  2011.  SSE4 is the next fastest and is supported by most current machines.  
*/


#include <dlib/image_processing/frontal_face_detector.h>
//#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
//#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
	std::ostringstream stm ;
	stm << n ;
	return stm.str() ;
    }
}

inline string GetFileName(const string &path)
{
    size_t pos1;

    pos1 = path.rfind('\\');
    if(pos1 != string::npos){
	return path.substr(pos1+1, path.size()-pos1-1);
    }

    pos1 = path.rfind('/');
    if(pos1 != string::npos){
	return path.substr(pos1+1, path.size()-pos1-1);
    }

    return path;
}

int main(int argc, char** argv)
{  
    try
	{
	    // This example takes in a shape model file and then a list of images to
	    // process.  We will take these filenames in as command line arguments.
	    // Dlib comes with example images in the examples/faces folder so give
	    // those as arguments to this program.
	    if (argc == 1)
		{
		    cout << "Call this program like this:" << endl;
		    cout << "./face_landmark_detection_ex shape_predictor_68_face_landmarks.dat faces/*.jpg" << endl;
		    cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
		    cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
		    return 0;
		}

	    // We need a face detector.  We will use this to get bounding boxes for
	    // each face in an image.
	    frontal_face_detector detector = get_frontal_face_detector();
	    // And we also need a shape_predictor.  This is the tool that will predict face
	    // landmark positions given an image and face bounding box.  Here we are just
	    // loading the model from the shape_predictor_68_face_landmarks.dat file you gave
	    // as a command line argument.
	    shape_predictor sp;
	    deserialize(argv[1]) >> sp;


	    //image_window win, win_faces;
	    // Loop over all the images provided on the command line.
	    for (int i = 2; i < argc; ++i)
		{
		    DIR* dp=opendir(argv[i]);

		    struct dirent* dent;
		    do{
			dent = readdir(dp);
			if (dent!=NULL) {

			    std::string filename = dent->d_name;
			    if ( filename == "." || filename == ".." || filename == ".DS_Store") continue;

			    array2d<rgb_pixel> img;
			    std::string filepath = argv[i] + filename;
			    load_image(img, filepath);
			    // Make the image larger so we can detect small faces.
			    pyramid_up(img);

			    // Now tell the face detector to give us a list of bounding boxes
			    // around all the faces in the image.
			    std::vector<rectangle> dets = detector(img);

			    // Now we will go ask the shape_predictor to tell us the pose of
			    // each face we detected.
			    std::vector<full_object_detection> shapes;
			    for (unsigned long j = 0; j < dets.size(); ++j)
				{
				    full_object_detection shape = sp(img, dets[j]);

				    // You get the idea, you can get all the face part locations if
				    // you want them.  Here we just store them in shapes so we can
				    // put them on the screen.
				    shapes.push_back(shape);
				}

			    // We can also extract copies of each face that are cropped, rotated upright,
			    // and scaled to a standard size as shown here:
			    dlib::array<array2d<rgb_pixel> > face_chips;
			    extract_image_chips(img, get_face_chip_details(shapes), face_chips);

			    if (dets.size() > 0) {
				for (int i =0; i< dets.size(); i++) {
				    std::string filename = patch::to_string(i) + "_" + dent->d_name;
				    std::string save_path = "./result_faces/" + filename;				    

				    dlib::chip_details img_details = get_face_chip_details(shapes[i], 256);
				    cout << filename << ':' << img_details.rect << ':' << img_details.angle << endl;
				    save_jpeg(face_chips[i], save_path);
				}
			    }

			}
		    }while(dent!=NULL);
		    closedir(dp);

		}
	}
    catch (exception& e)
	{
	    cout << "\nexception thrown!" << endl;
	    cout << e.what() << endl;
	}
}

// ----------------------------------------------------------------------------------------

