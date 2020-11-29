#include <opencv2/opencv.hpp>
#include "base64.h"
#include <iostream>
#include "crow_all.h"
using namespace cv;
using namespace std;
using namespace crow;



class ImageContainer {
public:
	Mat mat;
	string base64;
	string encodeImage(Mat inputImage)
	{
		vector<uchar> buf;
		imencode(".jpg", inputImage, buf);
		auto* enc_msg = reinterpret_cast<unsigned char*>(buf.data());
		string encoded = base64_encode(enc_msg, buf.size());
		return encoded;
	}

	Mat decodeImage(string encodedImage)
	{
		string dec_jpg = base64_decode(encodedImage);
		vector<uchar> data(dec_jpg.begin(), dec_jpg.end());
		Mat decoded = imdecode(Mat(data), 1);
		return decoded;
	}


	ImageContainer(Mat image) {
		mat = image;
		base64 = encodeImage(image);
	}

	ImageContainer(String imageString) {
		mat = decodeImage(imageString);
		base64 = imageString;
	}

	void resizeImage(int height, int width)
	{	
		cout << "original image height: " << size(mat).height << endl;
		cout << "original image width: " << size(mat).width << endl;

		Size newSize(500, 500);
		resize(mat, mat, Size(height, width));
		cout << "new image height: " << size(mat).height << endl;
		cout << "new image width: " << size(mat).width << endl;
		base64 = encodeImage(mat);

	}

};


void stringToText(string input, string filename)
{
	ofstream out(filename);
	out << input;
	out.close();
}

String textToString(string filename)
{
	string output;

	ifstream f(filename); //taking file as inputstream
	if (f) {
		ostringstream ss;
		ss << f.rdbuf(); // reading data
		output = ss.str();
	}
	return output;

}

int main(int argc, char** argv)
{
	
	SimpleApp app;

	CROW_ROUTE(app, "/resize_image").methods("POST"_method)
		([](const crow::request& req) {
		ostringstream os;

		try
		{
			auto info = crow::json::load(req.body);
			string input_base64 = info["input_jpeg"].s();
			int  width = info["desired_width"].i();
			int  height = info["desired_height"].i();
			
			
			ImageContainer image(input_base64);
			image.resizeImage(height, width);

			crow::json::wvalue result;
			result["code"] = 200;
			result["message"] = "success";
			result["output_jpeg"] = image.base64;
			os << crow::json::dump(result);

			return crow::response{ 200,os.str() };
		}
		catch (std::exception& e)
		{
			crow::json::wvalue result;
			result["code"] = 404;
			result["message"] = "failed to convert input_image, check your image string!";
			os << crow::json::dump(result);
			return crow::response(404,os.str());
		}


			});

	app.port(8080).run();
	return 0;




}