#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

const float WRAP_WIDTH = 420, WRAP_HEIGHT = 596;

Mat PreprocessImage(const Mat& img) {
	Mat result;
	cvtColor(img, result, COLOR_BGR2GRAY);
	GaussianBlur(result, result, Size(3, 3), 3, 0);
	Canny(result, result, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(result, result, kernel);
	return result;
}

std::vector<Point> GetDocumentContours(const Mat& image) {
	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;

	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<Point>> approximated_poly_contours(contours.size());
	std::vector<Point> result;
	int max_area = 0;

	for (size_t i = 0; i < contours.size(); i++){
		int area = contourArea(contours[i]);
		std::cout << area << std::endl;
		if (area > 1000){
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], approximated_poly_contours[i], 0.05 * peri, true);
			std::cout << "SIZE : " << approximated_poly_contours[i].size() << std::endl;
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


std::vector<Point> ReorderRectanglePoints(const std::vector<Point>& points)
{
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

int main() {
	std::string path = "Resources/paper2.jpg";
	Mat original_image = imread(path);
	Mat preproccessed_image = PreprocessImage(original_image);

	imshow("Original", original_image);
	imshow("Preproccessed image", preproccessed_image);

	std::vector<Point> document_vertices = GetDocumentContours(preproccessed_image);
	if (document_vertices.empty()) {
		std::cout << "Samara" << std::endl;
		return 1;
	}

	document_vertices = ReorderRectanglePoints(document_vertices);
	Mat warp_image = GetWarp(original_image, document_vertices);

	imshow("Image", warp_image);
	waitKey(0);

}