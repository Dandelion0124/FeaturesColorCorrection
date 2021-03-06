#include "function.h"

void readLabels(string lbfn, int& w, int& h, int& regionum, vector<int>& labels)
{
	fstream fin (lbfn, ios::in);
	if (fin.is_open() == false)
	{
		cout << "failed to read " << lbfn << endl;
		return ;
	}

	regionum = 0;

	fin >> w >> h;
	labels.resize(w*h);
	for (int i = 0; i < w*h; ++i)
	{
		fin >> labels[i];
		if (labels[i] > regionum)
			regionum = labels[i];
	}
	regionum = regionum + 1;   //计数从0开始

	fin.close();
}

void saveLabels(vector<int> labels, int w, int h, string lbfn)
{
	ofstream fout(lbfn.c_str(), ios::out);
	if (fout.is_open() == false)
	{
		cout << "failed to write " << lbfn << endl;
		return ;
	}

	fout << w << ' ' << h << endl;
	for (int j = 0; j < h; ++j)
	{
		for (int i = 0; i < w; ++i)
		{
			fout << labels[j*w+i] << ' ';
		}
		fout << endl;
	}
	fout.close();
}

void readFeatures(string ffn, vector<Point2f>& features)
{	
	fstream fin(ffn.c_str(), ios::in);
	if (fin.is_open() == false)
	{
		cout << "CStereo::readFeaturePts: failed to open " << ffn << std::endl;
		return;
	}

	int num;   //features 数目
	features.clear();

	fin >> num;
	for (int i = 0; i < num; i ++)
	{
		float x, y;
		int type;
		float response;
		
		fin >> x;  
		fin >> y;  
		fin >> type;    
		fin >> response;

		Point2f pt( x, y) ;
		features.push_back(pt);		
	}

	fin.close();
	cout << "read features from " << ffn << " done. " << num << " points."  << endl;
}

void readSiftFeatures(string sffn, vector<Point2f>& features)
{
	fstream fin(sffn.c_str(), ios::in);
	if (fin.is_open() == false)
	{
		cout << "CStereo::readFeaturePts: failed to open " << sffn << std::endl;
		return;
	}

	int num;   //features 数目
	features.clear();

	fin >> num;
	for (int i = 0; i < num; i ++)
	{
		float x, y;
		
		fin >> x;  
		fin >> y;  
		
		Point2f pt( x, y) ;
		features.push_back(pt);		
	}

	fin.close();
	cout << "read features from " << sffn << " done. " << num << " points."  << endl;
}

void showFeatures(Mat im, vector<Point2f>& features, cv::Scalar color, string sfn)
{
	Mat tim = im.clone();
	for (int i = 0; i < features.size(); i ++)
	{
		Point2i tpt ((int)features[i].x, (int)features[i].y);
		circle(tim, tpt, 3, color);  
	}
	imwrite(sfn, tim);
}


void readMatches(string mfn, vector<Point2f>& features1, vector<Point2f>& features2)
{
	fstream fin(mfn.c_str(), std::ios::in);
	if (fin.is_open() == false)
	{
		cout << "failed to open " << mfn << std::endl;
		return ;
	}

	features1.clear();
	features2.clear();

	int matchnum;
	float y, sx, tx;
	float ncc, prior;

	fin >> matchnum;
	for (int i = 0; i < matchnum; ++ i )
	{
		fin >> y >> sx >> tx >> ncc >> prior;

		Point2f pt1(sx, y);
		Point2f pt2(tx, y);

		features1.push_back(pt1);
		features2.push_back(pt2);
	}
	fin.close();

	cout << "read matches from " << mfn << " done. " << matchnum << " matches." << endl;
}

void readSiftMatches(string sfmfn, vector<Point2f>& features1, vector<Point2f>& features2)
{
	fstream fin(sfmfn.c_str(), std::ios::in);
	if (fin.is_open() == false)
	{
		cout << "failed to open " << sfmfn << std::endl;
		return ;
	}

	features1.clear();
	features2.clear();

	int matchnum;
	float x1, y1, x2, y2;

	fin >> matchnum;
	for (int i = 0; i < matchnum; ++ i )
	{
		fin >> x1 >> y1 >> x2 >> y2;

		Point2f pt1(x1, y1);
		Point2f pt2(x2, y2);

		features1.push_back(pt1);
		features2.push_back(pt2);
	}
	fin.close();

	cout << "read matches done. " << matchnum << " matches." << endl;
}

void showMatches(Mat im1, Mat im2, vector<Point2f>& pts1, vector<Point2f>& pts2, string smfn)
{
	int h = im1.rows;
	int w = im1.cols;


	Mat canvas(h, w * 2, CV_8UC3);
	im1.copyTo(canvas(cv::Rect(0, 0, w, h)));
	im2.copyTo(canvas(cv::Rect(w, 0, w, h)));

	for (int i = 0; i < pts1.size(); ++i)
	{
		Point2i pt1 (pts1[i].x, pts1[i].y);
		Point2i pt2 (pts2[i].x + w, pts2[i].y);

		cv::line(canvas, pt1, pt2, cv::Scalar(0, 100, 0));
		cv::circle(canvas, pt1, 1, cv::Scalar(100, 0, 0));
		cv::circle(canvas, pt2, 1, cv::Scalar(100,0,0));
	}

	if (smfn != "")
	{
		imwrite(smfn, canvas);
	}
	
}