package com.example.cameratest3;

import org.opencv.core.Mat;

public class LaneDetectionView {
	private static final String TAG = "LaneDetectionView";

	public void detect(Mat srcColor, Mat lanes) {
		nativeDetect(srcColor.getNativeObjAddr(), lanes.getNativeObjAddr());
	}

	public void perspectiveTransform(Mat srcColor, Mat dst) {
		birdeye(srcColor.getNativeObjAddr(), dst.getNativeObjAddr());
	}
	
	public void getROI(Mat srcColor, Mat dst) {
		nativeGetROI(srcColor.getNativeObjAddr(), dst.getNativeObjAddr());
	}
	
	
	//build an ROI 
	public native void nativeGetROI(long inputImage,long outputImage);

	// Use perspective transform to see the image in bird-view
	public native void birdeye(long inputImage, long outputImage);

	// keep only region of interest by mask and make blend on color image
	public native void nativeDetect(long inputImage,long inputLanes);

}
