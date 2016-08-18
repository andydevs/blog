//-----------------------------------------------------------------------------------
// Program: JuliaSet
// 
// Generates Julia set images
//
// Author:  Anshul Kharbanda
// Created: 8 - 14 - 2016
//-----------------------------------------------------------------------------------

// Headers being used
#include "CImg/CImg.h"
#include "JuliaSet/juliaset.h"
#include "JuliaSet/colormaps.h"

// Libraries being used
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>

// Namespaces being used
using namespace std;
using namespace cimg_library;
using namespace juliaset;
using namespace juliaset::colormap;

/**
 * The main function of the program
 *
 * @param argc the number of command line arguments
 * @param argv the command line arguments
 *
 * @return exit code
 */
int main(int argc, char const *argv[])
{
	// ------------------------------CONFIG------------------------------

	// CImg descriptor
	cimg_usage("Generates JuliaSet images.");

	// Image options
	bool showCmaps  = cimg_option("-cmaps", false,		  "Lists the cmaps");
	unsigned imgx   = cimg_option("-imgx",  1920, 		  "The image width");
	unsigned imgy   = cimg_option("-imgy",  1080, 		  "The image height");
	double real     = cimg_option("-cr",    0.0,  		  "The constant real component");
	double imag     = cimg_option("-ci",    0.0,  		  "The constant imaginary component");
	double zoom     = cimg_option("-zoom",  1.0,  		  "The zoom scale of the image");
	double offx     = cimg_option("-offx",  0.0,  		  "The x offset of the image");
	double offy     = cimg_option("-offy",  0.0,  		  "The y offset of the image");
	double rot      = cimg_option("-rot",   0.0,  		  "The angle of rotation of the image (in degrees)");
	string savename = cimg_option("-save",  "jimage.jpg", "The file to save the image to");
	string cmapname = cimg_option("-cmap",  "noir",       "The colormapping to use");

	// Image config
	Config cfg(zoom, offx, offy, rot);

	// Initialize colormaps
	initColorMap();

	// Show cmaps option
	if (showCmaps)
	{
		// Get cmaps
		vector<string> v = getColorMaps();

		// Print cmaps
		cout << "Available colormaps:" << endl;
		for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
			cout << "\t" << *it << endl;

		// Return 0
		return 0;
	}

	// Image colormap
	const ColorMapRGB* cmap;
	if (hasColorMap(cmapname))
		cmap = getColorMap(cmapname);
	else
	{
		cout << "Error! Colormap is not defined: " << cmapname << endl;
		return 1;
	}

	// -----------------------------CONSTANTS-----------------------------

	// Complex values
	const complex<double> cons(real, imag);   // Constant
	const complex<double> off(offx, offy); // Offset

	// Image (with 3 color channels)
	CImg<char> jimage(imgx, imgy, 1, 3);

	// -----------------------------ALGORITHM-----------------------------

	// Print dimensions
	cout << "Generating..." << endl;

	// Start clock
	double time = clock();

	// Generate julia set image
	int iter = generateJuliaSetImage(jimage, cons, cfg, cmap);

	// End clock
	time = (clock() - time) / CLOCKS_PER_SEC;

	// ----------------------------SAVE AND END---------------------------

	// Save image
	cout << "Saving..." << endl;
	jimage.save(savename.c_str());

	// Print end information
	cout << "Iterations: "     << iter << endl;
	cout << "Time (seconds): " << time << endl;

	// End program
	return 0;
}