package com.openglesbook.common;

import java.lang.Math;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public class ESTransform {
	public ESTransform() {
		mMatrixFloatBuffer = ByteBuffer.allocateDirect(16 * 4)
				.order(ByteOrder.nativeOrder()).asFloatBuffer();
	}

	public void scale(float sx, float sy, float sz) {
		mMatrix[0 * 4 + 0] *= sx;
		mMatrix[0 * 4 + 1] *= sx;
		mMatrix[0 * 4 + 2] *= sx;
		mMatrix[0 * 4 + 3] *= sx;

		mMatrix[1 * 4 + 0] *= sy;
		mMatrix[1 * 4 + 1] *= sy;
		mMatrix[1 * 4 + 2] *= sy;
		mMatrix[1 * 4 + 3] *= sy;

		mMatrix[2 * 4 + 0] *= sz;
		mMatrix[2 * 4 + 1] *= sz;
		mMatrix[2 * 4 + 2] *= sz;
		mMatrix[2 * 4 + 3] *= sz;
	}

	public void translate(float tx, float ty, float tz) {
		mMatrix[3 * 4 + 0] += (mMatrix[0 * 4 + 0] * tx + mMatrix[1 * 4 + 0]
				* ty + mMatrix[2 * 4 + 0] * tz);
		mMatrix[3 * 4 + 1] += (mMatrix[0 * 4 + 1] * tx + mMatrix[1 * 4 + 1]
				* ty + mMatrix[2 * 4 + 1] * tz);
		mMatrix[3 * 4 + 2] += (mMatrix[0 * 4 + 2] * tx + mMatrix[1 * 4 + 2]
				* ty + mMatrix[2 * 4 + 2] * tz);
		mMatrix[3 * 4 + 3] += (mMatrix[0 * 4 + 3] * tx + mMatrix[1 * 4 + 3]
				* ty + mMatrix[2 * 4 + 3] * tz);
	}

	public void rotate(float angle, float x, float y, float z) {
		float sinAngle, cosAngle;
		float mag = (float) Math.sqrt((double) (x * x + y * y + z * z));

		sinAngle = (float) Math.sin((double) (angle * Math.PI / 180.0));
		cosAngle = (float) Math.cos((double) (angle * Math.PI / 180.0));
		if (mag > 0.0f) {
			float xx, yy, zz, xy, yz, zx, xs, ys, zs;
			float oneMinusCos;
			float[] rotMat = new float[16];

			x /= mag;
			y /= mag;
			z /= mag;

			xx = x * x;
			yy = y * y;
			zz = z * z;
			xy = x * y;
			yz = y * z;
			zx = z * x;
			xs = x * sinAngle;
			ys = y * sinAngle;
			zs = z * sinAngle;
			oneMinusCos = 1.0f - cosAngle;

			rotMat[0 * 4 + 0] = (oneMinusCos * xx) + cosAngle;
			rotMat[0 * 4 + 1] = (oneMinusCos * xy) - zs;
			rotMat[0 * 4 + 2] = (oneMinusCos * zx) + ys;
			rotMat[0 * 4 + 3] = 0.0F;

			rotMat[1 * 4 + 0] = (oneMinusCos * xy) + zs;
			rotMat[1 * 4 + 1] = (oneMinusCos * yy) + cosAngle;
			rotMat[1 * 4 + 2] = (oneMinusCos * yz) - xs;
			rotMat[1 * 4 + 3] = 0.0F;

			rotMat[2 * 4 + 0] = (oneMinusCos * zx) - ys;
			rotMat[2 * 4 + 1] = (oneMinusCos * yz) + xs;
			rotMat[2 * 4 + 2] = (oneMinusCos * zz) + cosAngle;
			rotMat[2 * 4 + 3] = 0.0F;

			rotMat[3 * 4 + 0] = 0.0F;
			rotMat[3 * 4 + 1] = 0.0F;
			rotMat[3 * 4 + 2] = 0.0F;
			rotMat[3 * 4 + 3] = 1.0F;

			matrixMultiply(rotMat, mMatrix);
		}
	}

	public void frustum(float left, float right, float bottom, float top,
			float nearZ, float farZ) {
		float deltaX = right - left;
		float deltaY = top - bottom;
		float deltaZ = farZ - nearZ;
		float[] frust = new float[16];

		if ((nearZ <= 0.0f) || (farZ <= 0.0f) || (deltaX <= 0.0f)
				|| (deltaY <= 0.0f) || (deltaZ <= 0.0f))
			return;

		frust[0 * 4 + 0] = 2.0f * nearZ / deltaX;
		frust[0 * 4 + 1] = frust[0 * 4 + 2] = frust[0 * 4 + 3] = 0.0f;

		frust[1 * 4 + 1] = 2.0f * nearZ / deltaY;
		frust[1 * 4 + 0] = frust[1 * 4 + 2] = frust[1 * 4 + 3] = 0.0f;

		frust[2 * 4 + 0] = (right + left) / deltaX;
		frust[2 * 4 + 1] = (top + bottom) / deltaY;
		frust[2 * 4 + 2] = -(nearZ + farZ) / deltaZ;
		frust[2 * 4 + 3] = -1.0f;

		frust[3 * 4 + 2] = -2.0f * nearZ * farZ / deltaZ;
		frust[3 * 4 + 0] = frust[3 * 4 + 1] = frust[3 * 4 + 3] = 0.0f;

		matrixMultiply(frust, mMatrix);
	}

	public void perspective(float fovy, float aspect, float nearZ, float farZ) {
		float frustumW, frustumH;

		frustumH = (float) Math.tan(fovy / 360.0 * Math.PI) * nearZ;
		frustumW = frustumH * aspect;

		frustum(-frustumW, frustumW, -frustumH, frustumH, nearZ, farZ);
	}

	public void ortho(float left, float right, float bottom, float top,
			float nearZ, float farZ) {
		float deltaX = right - left;
		float deltaY = top - bottom;
		float deltaZ = farZ - nearZ;
		float[] orthoMat = makeIdentityMatrix();

		if ((deltaX == 0.0f) || (deltaY == 0.0f) || (deltaZ == 0.0f))
			return;

		orthoMat[0 * 4 + 0] = 2.0f / deltaX;
		orthoMat[3 * 4 + 0] = -(right + left) / deltaX;
		orthoMat[1 * 4 + 1] = 2.0f / deltaY;
		orthoMat[3 * 4 + 1] = -(top + bottom) / deltaY;
		orthoMat[2 * 4 + 2] = -2.0f / deltaZ;
		orthoMat[3 * 4 + 2] = -(nearZ + farZ) / deltaZ;

		matrixMultiply(orthoMat, mMatrix);
	}

	public void matrixMultiply(float[] srcA, float[] srcB) {
		float[] tmp = new float[16];
		int i;

		for (i = 0; i < 4; i++) {
			tmp[i * 4 + 0] = (srcA[i * 4 + 0] * srcB[0 * 4 + 0])
					+ (srcA[i * 4 + 1] * srcB[1 * 4 + 0])
					+ (srcA[i * 4 + 2] * srcB[2 * 4 + 0])
					+ (srcA[i * 4 + 3] * srcB[3 * 4 + 0]);

			tmp[i * 4 + 1] = (srcA[i * 4 + 0] * srcB[0 * 4 + 1])
					+ (srcA[i * 4 + 1] * srcB[1 * 4 + 1])
					+ (srcA[i * 4 + 2] * srcB[2 * 4 + 1])
					+ (srcA[i * 4 + 3] * srcB[3 * 4 + 1]);

			tmp[i * 4 + 2] = (srcA[i * 4 + 0] * srcB[0 * 4 + 2])
					+ (srcA[i * 4 + 1] * srcB[1 * 4 + 2])
					+ (srcA[i * 4 + 2] * srcB[2 * 4 + 2])
					+ (srcA[i * 4 + 3] * srcB[3 * 4 + 2]);

			tmp[i * 4 + 3] = (srcA[i * 4 + 0] * srcB[0 * 4 + 3])
					+ (srcA[i * 4 + 1] * srcB[1 * 4 + 3])
					+ (srcA[i * 4 + 2] * srcB[2 * 4 + 3])
					+ (srcA[i * 4 + 3] * srcB[3 * 4 + 3]);
		}

		mMatrix = tmp;
	}

	public void matrixLoadIdentity() {
		for (int i = 0; i < 16; i++)
			mMatrix[i] = 0.0f;

		mMatrix[0 * 4 + 0] = 1.0f;
		mMatrix[1 * 4 + 1] = 1.0f;
		mMatrix[2 * 4 + 2] = 1.0f;
		mMatrix[3 * 4 + 3] = 1.0f;
	}

	private float[] makeIdentityMatrix() {
		float[] result = new float[16];

		for (int i = 0; i < 16; i++)
			result[i] = 0.0f;

		result[0 * 4 + 0] = 1.0f;
		result[1 * 4 + 1] = 1.0f;
		result[2 * 4 + 2] = 1.0f;
		result[3 * 4 + 3] = 1.0f;

		return result;
	}

	public FloatBuffer getAsFloatBuffer() {
		mMatrixFloatBuffer.put(mMatrix).position(0);
		return mMatrixFloatBuffer;
	}

	public float[] get() {
		return mMatrix;
	}

	private float[] mMatrix = new float[16];
	private FloatBuffer mMatrixFloatBuffer;

}