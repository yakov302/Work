#include "mu_test.h"
#include "image.hpp"
#include <fstream>

bool cctor(image::Image<uint_fast16_t> a_image)
{
	return a_image.getPixel(1,1) == 80 
		&& a_image.getPixel(2,2) == 70
		&& a_image.getPixel(6,8) == 200;
}

BEGIN_TEST(copy_and_cctor)

	// *** Black and white imags ***

	image::Image<uint_fast16_t> image(8,8,"P2",255);
	image.setPixel(1,1, 80);
	image.setPixel(2,2, 70);
	image.setPixel(6,8, 200);

	image::Image<uint_fast16_t> copy;
	copy = image;

    ASSERT_EQUAL(copy.getPixel(1,1), image.getPixel(1,1));
	ASSERT_EQUAL(copy.getPixel(2,2), image.getPixel(2,2));
	ASSERT_EQUAL(copy.getPixel(6,8), image.getPixel(6,8));
	ASSERT_EQUAL(cctor(image),true);

	// *** Colored imags ***

	image::Image<uint_fast16_t> coloredImage(8,8,"P3",255);
	image.setPixel(1,1, 80);
	image.setPixel(2,2, 70);
	image.setPixel(6,8, 200);

	image::Image<uint_fast16_t> coloredCopy;
	coloredCopy = coloredImage;

    ASSERT_EQUAL(coloredCopy.getPixel(1,1), coloredImage.getPixel(1,1));
	ASSERT_EQUAL(coloredCopy.getPixel(2,2), coloredImage.getPixel(2,2));
	ASSERT_EQUAL(coloredCopy.getPixel(6,8), coloredImage.getPixel(6,8));
	ASSERT_EQUAL(cctor(image),true);

END_TEST

image::Image<uint_fast16_t> generate()
{
	image::Image<uint_fast16_t> temp(4,4,"P2",255);
	temp.setPixel(1,1, 80);
	temp.setPixel(2,2, 70);
	return temp;
}

image::Image<uint_fast16_t> generateColored()
{
	image::Image<uint_fast16_t> temp(8,8,"P3",255);
	temp.setPixel(1,1, 80);
	temp.setPixel(2,2, 70);
	temp.setPixel(6,8, 200);
	return temp;
}

image::Image<uint_fast16_t> Transform(image::Image<uint_fast16_t> a_image)
{
	return a_image;
}

BEGIN_TEST(move_copy_and_cctor)

	// *** Black and white imags ***

	image::Image<uint_fast16_t> image;
	image = generate();
    ASSERT_EQUAL(image.getPixel(1,1),80);
	ASSERT_EQUAL(image.getPixel(2,2), 70);

	ASSERT_EQUAL(Transform(generate()).getPixel(1,1),80);
	ASSERT_EQUAL(Transform(generate()).getPixel(2,2), 70);

	// *** Colored imags ***

	image::Image<uint_fast16_t> coloresImage;
	coloresImage = generateColored();
    ASSERT_EQUAL(coloresImage.getPixel(1,1),80);
	ASSERT_EQUAL(coloresImage.getPixel(2,2), 70);
	ASSERT_EQUAL(coloresImage.getPixel(6,8), 200);

	ASSERT_EQUAL(Transform(generateColored()).getPixel(1,1),80);
	ASSERT_EQUAL(Transform(generateColored()).getPixel(2,2), 70);
	ASSERT_EQUAL(Transform(generateColored()).getPixel(6,8), 200);

END_TEST

BEGIN_TEST(brighten)

	// *** Black and white imags ***

	std::ifstream cat("../data/cat.pgm");
	image::Image<uint_fast16_t> image = image::read<uint_fast16_t>(cat);
	brighten(image, 30);
	std::ofstream brightenCat("../data/brightenCat.pgm");
	image::save<uint_fast16_t>(image, brightenCat);

	// *** Colored imags ***

	std::ifstream coloredCat("../data/cat.ppm");
	image::Image<uint_fast16_t> coloredImage = image::read<uint_fast16_t>(coloredCat);
	brighten(coloredImage, 30);
	std::ofstream brightenColoredCat("../data/brightenCat.ppm");
	image::save<uint_fast16_t>(coloredImage, brightenColoredCat);

	ASSERT_PASS();

END_TEST

BEGIN_TEST(change_color_scale)

	// *** Black and white imags ***

	std::ifstream cat("../data/cat.pgm");
	image::Image<uint_fast16_t> image = image::read<uint_fast16_t>(cat);
	changeColorScale(image, (uint_fast16_t)4);
	std::ofstream changeColorScaleCat("../data/changeColorScaleCat.pgm");
	image::save (image, changeColorScaleCat);

	// *** Colored imags ***

	std::ifstream coloredCat("../data/cat.ppm");
	image::Image<uint_fast16_t> coloredImage = image::read<uint_fast16_t>(coloredCat);
	changeColorScale(coloredImage, (uint_fast16_t)4);
	std::ofstream changeColorScaleColoredCat("../data/changeColorScaleCat.ppm");
	image::save (coloredImage, changeColorScaleColoredCat);

	ASSERT_PASS();

END_TEST

BEGIN_TEST(reduce_pixels)

	// *** Black and white imags ***

	std::ifstream cat("../data/cat.pgm");
	image::Image<uint_fast16_t> image = image::read<uint_fast16_t>(cat);
	reducePixels(image, 3);
	std::ofstream pixelateCat("../data/reducePixelsCat.pgm");
	image::save (image, pixelateCat);

	// *** Colored imags ***

	std::ifstream coloredCat("../data/cat.ppm");
	image::Image<uint_fast16_t> coloredImage = image::read<uint_fast16_t>(coloredCat);
	reducePixels(coloredImage, 3);
	std::ofstream pixelateColoredCat("../data/reducePixelsCat.ppm");
	image::save (coloredImage, pixelateColoredCat);

	ASSERT_PASS();

END_TEST

BEGIN_TEST(blur)

	// *** Black and white imags ***

	std::ifstream cat("../data/cat.pgm");
	image::Image<uint_fast16_t> image = image::read<uint_fast16_t>(cat);
	image::Image<uint_fast16_t> blurImage = blur(image);
	std::ofstream blurCat("../data/blurCat.pgm");
	image::save (blurImage, blurCat);

	// *** Colored imags ***

	std::ifstream coloredCat("../data/cat.ppm");
	image::Image<uint_fast16_t> coloredImage = image::read<uint_fast16_t>(coloredCat);
	image::Image<uint_fast16_t> blurColoredImage = blur(coloredImage);
	std::ofstream blurColoredCat("../data/blurCat.ppm");
	image::save (blurColoredImage, blurColoredCat);

	ASSERT_PASS();

END_TEST

BEGIN_TEST(sharp)

	// *** Black and white imags ***

	std::ifstream cat("../data/cat.pgm");
	image::Image<uint_fast16_t> image = image::read<uint_fast16_t>(cat);
	image::Image<uint_fast16_t> sharpImage = sharp(image);
	std::ofstream sharpCat("../data/sharpCat.pgm");
	image::save (sharpImage, sharpCat);

	// *** Colored imags ***

	std::ifstream coloredCat("../data/cat.ppm");
	image::Image<uint_fast16_t> coloredImage = image::read<uint_fast16_t>(coloredCat);
	image::Image<uint_fast16_t> sharpColoredImage = sharp(coloredImage);
	std::ofstream sharpColoredCat("../data/sharpCat.ppm");
	image::save (sharpColoredImage, sharpColoredCat);

	ASSERT_PASS();

END_TEST

BEGIN_SUITE(TEST)

	TEST(copy_and_cctor)
	TEST(move_copy_and_cctor)
	TEST(brighten)
	TEST(change_color_scale)
	TEST(reduce_pixels)
	TEST(blur)
	TEST(sharp)

END_SUITE
