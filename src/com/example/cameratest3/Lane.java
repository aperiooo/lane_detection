package com.example.cameratest3;

import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Scalar;
import org.opencv.imgproc.Imgproc;

public class Lane {

	/*
	 * A Line is defined from two points (x1, y1) and (x2, y2) as follows: y -
	 * y1 = (y2 - y1) / (x2 - x1) * (x - x1) Each line has its own slope and
	 * intercept (bias).斜率和截距（偏差）
	 */

	public double x1;
	public double x2;
	public double y1;
	public double y2;

	// public double slope;
	// public double bias;

	/**
	 * 计算线的斜率
	 * 
	 * @return 斜率
	 */
	public double computeSlope() {
		// Double.MIN_VALUE 能表示的最小正值
		return (this.y2 - this.y1) / (this.x2 - this.x1 + Double.MIN_VALUE);
	}

	/**
	 * 计算线的偏差
	 * 
	 * @return 偏差
	 */
	public double computeBias() {
		return this.y1 - this.computeSlope() * this.x1;
	}

	// /**
	// * 获得坐标
	// *
	// * @return double[] coords
	// */
	// public double[] getCoords() {
	// double[] coords = { this.x1, this.y1, this.x2, this.y2 };
	// return coords;
	// }
	//
	// public void setCoords(double x1, double y1, double x2, double y2) {
	// this.x1 = x1;
	// this.y1 = y1;
	// this.x2 = x2;
	// this.y2 = y2;
	// }
	/**
	 * draw a line on image
	 * 
	 * @param img
	 *            Mat
	 * @param color
	 *            Scalar
	 * @param thickness
	 *            int
	 */
	public void draw(Mat img, Scalar color, int thickness) {
		Point pt1 = new Point(x1, y1);
		Point pt2 = new Point(x2, y2);
		Imgproc.line(img, pt1, pt2, color, thickness);
	}

	@Override
	public String toString() {
		return "lane  x1:" + this.x1 + " y1:" + this.y1 + " x2:" + this.x2
				+ " y2:" + this.y2 + " slope:" + this.computeSlope() + " bias:"
				+ this.computeBias();
	}
}
