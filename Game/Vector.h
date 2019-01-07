#pragma once

class Vector2
{
public:
	float x, y;

public:
	// <ベクトルはそのまま>
	constexpr inline Vector2 operator +() const { return *this; }

	// <ベクトルを反転>
	constexpr inline Vector2 operator -() const { return *this*-1; }

	// <ベクトルを加算>
	constexpr inline Vector2 operator +(const Vector2& other) const { return{ x + other.x, y + other.y }; }

	// <ベクトルを減算>
	constexpr inline Vector2 operator -(const Vector2& other) const { return{ x - other.x, y - other.y }; }

	// <ベクトルをスケール>
	constexpr inline Vector2 operator *(const Vector2& scale) const { return{ x * scale.x, y * scale.y }; }

	// <ベクトルをスケール>
	constexpr inline Vector2 operator *(float scale) const { return{ x * scale, y * scale }; }

	// <ベクトルをスケール>
	constexpr inline Vector2 operator /(const Vector2& scale) const { return{ x / scale.x, y / scale.y }; }

	// <ベクトルをスケール>
	constexpr inline Vector2 operator /(float scale) const { return{ x / scale, y / scale }; }


	inline Vector2& operator +=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	inline Vector2& operator -=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	inline Vector2& Vector2::operator *=(const Vector2& scale)
	{
		x *= scale.x;
		y *= scale.y;
		return *this;
	}

	inline Vector2& operator *=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	inline Vector2& Vector2::operator /=(const Vector2& scale)
	{
		x /= scale.x;
		y /= scale.y;
		return *this;
	}

	inline Vector2& operator /=(float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}

	// 比較演算子のオーバーロード
	bool operator==(const Vector2& p) { return ((static_cast<int>(this->x) == static_cast<int>(p.x)) && (static_cast<int>(this->y) == static_cast<int>(p.y))); };
	bool operator!=(const Vector2& p) { return ((static_cast<int>(this->x) != static_cast<int>(p.x)) && (static_cast<int>(this->y) != static_cast<int>(p.y))); };

public:

	void Set(float x_, float y_);

	Vector2 Add(Vector2* vec);	// 2Dベクトルの加算
	Vector2 Sub(Vector2* vec);	// 2Dベクトルの減算
	Vector2 Mul(float mul);		// 2Dベクトルの定数倍
	Vector2 Div(float div);

	Vector2 Normalized();				// 2Dベクトルの正規化
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

	Vector2 TranslateTowards(const Vector2& from, const Vector2& to, float maxDelta);

	bool CrossPoint(Vector2* vec1_gool, Vector2* vec2_start, Vector2* vec2_gool, Vector2* output);// 線分と線分の交点を求める
};
