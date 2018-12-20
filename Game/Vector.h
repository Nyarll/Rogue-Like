#pragma once

class Vector2
{
public:
	float x, y;

public:

	void Set(float x_, float y_);

	Vector2 Add(Vector2* vec);	// 2Dベクトルの加算
	Vector2 Sub(Vector2* vec);	// 2Dベクトルの減算
	Vector2 Mul(float mul);		// 2Dベクトルの定数倍
	Vector2 Div(float div);

	Vector2 Nomalize();				// 2Dベクトルの正規化
	float Dot(Vector2* vec);	// 2Dベクトル同士の内積
	float Cross(Vector2* vec);	// 2Dベクトル同士の外積

	Vector2 Rotate(float rad);	// 2Dベクトルをrad分回転させる

	float Angle();					// 2Dベクトルの角度
	float Angle2(Vector2* vec);	// 2Dベクトル間の角度
	float Length();					// 2Dベクトルの長さ
	float LengthSquared();			// 2Dベクトルの長さの二乗
	float LengthTo(Vector2* vec);// 2Dベクトル間の距離
	float LengthSquaredTo(Vector2* vec);	// 2Dベクトル間の距離の二乗

	void Decompose(Vector2* vec, Vector2* outvec1, Vector2* outvec2);	// 2Dベクトルを分解

	bool CrossPoint(Vector2* vec1_gool, Vector2* vec2_start, Vector2* vec2_gool, Vector2* output);// 線分と線分の交点を求める
};
