#include <opencv2/core/utils/logger.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <tesseract/baseapi.h>

using namespace cv;

const float WRAP_WIDTH = 630, WRAP_HEIGHT = 894;

Mat PreprocessImage(const Mat& img) {
	Mat result;
	cvtColor(img, result, COLOR_BGR2GRAY);
	GaussianBlur(result, result, Size(5, 5), 3, 0);
	Canny(result, result, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(result, result, kernel);
	return result;
}

std::vector<Point> GetDocumentContours(const Mat& img) {
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;

	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<Point>> approximated_poly_contours(contours.size());
	std::vector<Point> result;
	int max_area = 0;

	for (size_t i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		if (area > 10000){
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], approximated_poly_contours[i], 0.05 * peri, true);
			if (area > max_area && approximated_poly_contours[i].size() == 4) {
				result = { 
					approximated_poly_contours[i][0],
					approximated_poly_contours[i][1],
					approximated_poly_contours[i][2],
					approximated_poly_contours[i][3]
				};
				max_area = area;
			}
		}
	}
	return result;
}


std::vector<Point> ReorderRectanglePoints(const std::vector<Point>& points) {
	std::vector<Point> result;
	std::vector<int> sum_of_coords, subrtraction_of_points;

	for (size_t i = 0; i < 4; i++)	{
		sum_of_coords.push_back(points[i].x + points[i].y);
		subrtraction_of_points.push_back(points[i].x - points[i].y);
	}

	result.push_back(points[min_element(sum_of_coords.begin(),
							   sum_of_coords.end()) - sum_of_coords.begin()]);
	result.push_back(points[max_element(subrtraction_of_points.begin(),
							   subrtraction_of_points.end()) - subrtraction_of_points.begin()]);
	result.push_back(points[min_element(subrtraction_of_points.begin(),
							   subrtraction_of_points.end()) - subrtraction_of_points.begin()]);
	result.push_back(points[max_element(sum_of_coords.begin(),
							   sum_of_coords.end()) - sum_of_coords.begin()]);

	return result;
}

Mat GetWarp(const Mat& img, const std::vector<Point>& points) {
	Mat result;

	std::vector<Point2f> src = { 
		points[0],
		points[1],
		points[2],
		points[3]
	};

	std::vector<Point2f> dst = {
		{0.0f,0.0f},
		{WRAP_WIDTH,0.0f},
		{0.0f, WRAP_HEIGHT},
		{WRAP_WIDTH, WRAP_HEIGHT}
	};

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, result, matrix, Point(WRAP_WIDTH, WRAP_HEIGHT));

	return result;
}


void SaveTextFile(const std::string& filename, const std::string& text) {
	std::ofstream output;
	output.open("C:\\Users\\proko\\source\\ooop_2021_2022\\Semester 1\\Lab 3\\Text\\" + filename + ".txt");
	output << text;
	output.close();
}


int main() {
	utils::logging::setLogLevel(utils::logging::LogLevel::LOG_LEVEL_SILENT);

	std::cout << "==========================================\n\n"
			  << "Welcome to simple scan application\n\n\n"
			  << "[1] Scan file\n[2] Exit\n\n\n";

	char command;
	Mat original_image, warp_image, to_scan;

	std::unique_ptr<tesseract::TessBaseAPI> ocr = std::make_unique<tesseract::TessBaseAPI>();
	ocr->Init("C:\\vcpkg\\installed\\x64-windows\\tessdata\\tessdata", "eng", tesseract::OEM_DEFAULT);
	ocr->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);

	while (std::cin >> command && command != '2') {
		if (command == '1') {
			std::cout << "Enter name of photo\n";
			std::string path, text_path;
			std::cin >> path;
			text_path = path;
			path = "Resources/" + path;
			original_image = imread(path);

			if (original_image.empty()) {
				std::cout << "File " << path << " doesn't exist\n";
				continue;
			}

			std::vector<Point> document_vertices = GetDocumentContours(PreprocessImage(original_image));

			if (document_vertices.empty()) {
				std::cout << "Unable to extract document vertices\n";
				continue;
			}

			document_vertices = ReorderRectanglePoints(document_vertices);
			warp_image = GetWarp(original_image, document_vertices);

			cvtColor(warp_image, to_scan, COLOR_BGR2GRAY);
			std::cout << "\n\nExtracting text...\n\n";

		
			ocr->SetImage((uchar*)to_scan.data, to_scan.cols, to_scan.rows, 1, to_scan.cols);

			std::string filename = text_path.substr(0,text_path.find('.'));
			SaveTextFile(filename, ocr->GetUTF8Text());
			std::cout << "Successfully saved\n"
					  << "If you want to continue to work with program, close the Warp image window\n";
			imshow("Warp image", warp_image);
			waitKey(0);
		}
		else {
			std::cout << "Enter correct command\n";
		}
	}
}

