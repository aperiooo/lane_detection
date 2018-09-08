#include <jni.h>
#include "com_example_cameratest3_LaneDetectionView.h"

#include "opencv2/opencv.hpp"
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/objdetect.hpp>

#include <stdio.h>
#include <iostream>
#include <vector>
#include <android/log.h>

#define TAG "LaneDetectionView-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
using namespace std;
using namespace cv;

JNIEXPORT void JNICALL Java_com_example_cameratest3_LaneDetectionView_birdeye(
		JNIEnv *jenv, jobject, jlong srcColor, jlong dst) {
	LOGD("Java_com_example_cameratest3_LaneDetectionView_birdeye enter");
	try {
//		Mat& mGr = *(Mat*) srcColor;
//		Mat& mOp = *(Mat*) dst;
//		vector<KeyPoint> v;
//
//		Ptr<FeatureDetector> detector = FastFeatureDetector::create(50); //特征检测器
//		detector->detect(mGr, v);
//		for (unsigned int i = 0; i < v.size(); i++) {
//			const KeyPoint& kp = v[i];
//			circle(mOp, Point(kp.pt.x, kp.pt.y), 10, Scalar(255, 0, 0, 255));
//		}

	} catch (cv::Exception& e) {
		LOGD("birdeye caught cv::Exception: %s", e.what());
		jclass je = jenv->FindClass("org/opencv/core/CvException");
		if (!je)
			je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je, e.what());
	} catch (...) {
		LOGD("birdeye caught unknown exception");
		jclass je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je,
				"Unknown exception in JNI code LaneDetectionView.birdeye()");
	}

	LOGD("Java_com_example_cameratest3_LaneDetectionView_birdeye exit");
}

// Modify the camera image
JNIEXPORT void JNICALL Java_com_example_cameratest3_LaneDetectionView_nativeDetect(
		JNIEnv *jenv, jobject, jlong srcColor, jlong lanes) {
	LOGD("Java_com_example_cameratest3_LaneDetectionView_NativeDetect enter");
	try {
		Mat& mSrc = *(Mat*) srcColor;
		Mat& mLane = *(Mat*) lanes;

		Size size = mSrc.size();
		Mat roimask = Mat::zeros(size, CV_8UC4);
		//两个对角定点  ,矩阵颜色图像  ,由于线粗为-1,,此矩阵将被填充
		rectangle(roimask, Point(0, roimask.rows * 5 / 8),
				Point(roimask.cols, roimask.rows * 7 / 8),
				Scalar(255, 255, 255), -1, 8);

		// keep only region of interest by masking
		bitwise_and(roimask, mLane, roimask);
		//make blend on color image
		addWeighted(roimask, 0.8, mSrc, 1, 0, mSrc);

	} catch (cv::Exception& e) {
		LOGD("nativeDetect caught cv::Exception: %s", e.what());
		jclass je = jenv->FindClass("org/opencv/core/CvException");
		if (!je)
			je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je, e.what());
	} catch (...) {
		LOGD("nativeDetect caught unknown exception");
		jclass je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je,
				"Unknown exception in JNI code LaneDetectionView.nativeDetect()");
	}

	LOGD("Java_com_example_cameratest3_LaneDetectionView_NativeDetect exit");
}

JNIEXPORT void JNICALL Java_com_example_cameratest3_LaneDetectionView_nativeGetROI(
		JNIEnv *jenv, jobject, jlong srcColor, jlong dst) {
	LOGD("Java_com_example_cameratest3_LaneDetectionView_nativeGetROI enter");
	try {
		Mat& mSrc = *(Mat*) srcColor;
		Mat& mOp = *(Mat*) dst;

		Mat mask = Mat::zeros(mSrc.size(), CV_8UC1);
		int originalWidth = mSrc.cols;
		int originalHeight = mSrc.rows;
		vector<vector<Point> > contour;
		vector<Point> pts;
		pts.push_back(
				Point(originalWidth - (5 * originalWidth / 6),
						originalHeight - (originalHeight / 4)));
		pts.push_back(
				Point(originalWidth - (originalWidth / 6),
						originalHeight - (originalHeight / 4)));
		pts.push_back(
				Point(originalWidth - (originalWidth / 6),
						originalHeight - (originalHeight / 8)));
		pts.push_back(
				Point(originalWidth - (5 * originalWidth / 6),
						originalHeight - (originalHeight / 8)));
		contour.push_back(pts);
		drawContours(mask, contour, 0, Scalar::all(255), -1);

		mSrc.copyTo(mOp, mask);

	} catch (cv::Exception& e) {
		LOGD("nativeGetROI caught cv::Exception: %s", e.what());
		jclass je = jenv->FindClass("org/opencv/core/CvException");
		if (!je)
			je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je, e.what());
	} catch (...) {
		LOGD("nativeGetROI caught unknown exception");
		jclass je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je,
				"Unknown exception in JNI code LaneDetectionView.nativeGetROI()");
	}

	LOGD("Java_com_example_cameratest3_LaneDetectionView_nativeGetROI exit");
}
