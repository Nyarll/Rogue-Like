#pragma once

class Vector2
{
public:
	float x, y;

public:
	// <�x�N�g���͂��̂܂�>
	constexpr inline Vector2 operator +() const { return *this; }

	// <�x�N�g���𔽓]>
	constexpr inline Vector2 operator -() const { return *this*-1; }

	// <�x�N�g�������Z>
	constexpr inline Vector2 operator +(const Vector2& other) const { return{ x + other.x, y + other.y }; }

	// <�x�N�g�������Z>
	constexpr inline Vector2 operator -(const Vector2& other) const { return{ x - other.x, y - other.y }; }

	// <�x�N�g�����X�P�[��>
	constexpr inline Vector2 operator *(const Vector2& scale) const { return{ x * scale.x, y * scale.y }; }

	// <�x�N�g�����X�P�[��>
	constexpr inline Vector2 operator *(float scale) const { return{ x * scale, y * scale }; }

	// <�x�N�g�����X�P�[��>
	constexpr inline Vector2 operator /(const Vector2& scale) const { return{ x / scale.x, y / scale.y }; }

	// <�x�N�g�����X�P�[��>
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

	// ��r���Z�q�̃I�[�o�[���[�h
	bool operator==(const Vector2& p) { return ((static_cast<int>(this->x) == static_cast<int>(p.x)) && (static_cast<int>(this->y) == static_cast<int>(p.y))); };
	bool operator!=(const Vector2& p) { return ((static_cast<int>(this->x) != static_cast<int>(p.x)) && (static_cast<int>(this->y) != static_cast<int>(p.y))); };

public:

	void Set(float x_, float y_);

	Vector2 Add(Vector2* vec);	// 2D�x�N�g���̉��Z
	Vector2 Sub(Vector2* vec);	// 2D�x�N�g���̌��Z
	Vector2 Mul(float mul);		// 2D�x�N�g���̒萔�{
	Vector2 Div(float div);

	Vector2 Normalized();				// 2D�x�N�g���̐��K��
	float Dot(Vector2* vec);	// 2D�x�N�g�����m�̓���
	float Cross(Vector2* vec);	// 2D�x�N�g�����m�̊O��

	Vector2 Rotate(float rad);	// 2D�x�N�g����rad����]������

	float Angle();					// 2D�x�N�g���̊p�x
	float Angle2(Vector2* vec);	// 2D�x�N�g���Ԃ̊p�x
	float Length();					// 2D�x�N�g���̒���
	float LengthSquared();			// 2D�x�N�g���̒����̓��
	float LengthTo(Vector2* vec);// 2D�x�N�g���Ԃ̋���
	float LengthSquaredTo(Vector2* vec);	// 2D�x�N�g���Ԃ̋����̓��

	void Decompose(Vector2* vec, Vector2* outvec1, Vector2* outvec2);	// 2D�x�N�g���𕪉�

	Vector2 TranslateTowards(const Vector2& from, const Vector2& to, float maxDelta);

	bool CrossPoint(Vector2* vec1_gool, Vector2* vec2_start, Vector2* vec2_gool, Vector2* output);// �����Ɛ����̌�_�����߂�
};
