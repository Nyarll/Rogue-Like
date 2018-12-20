#pragma once

class Vector2
{
public:
	float x, y;

public:

	void Set(float x_, float y_);

	Vector2 Add(Vector2* vec);	// 2D�x�N�g���̉��Z
	Vector2 Sub(Vector2* vec);	// 2D�x�N�g���̌��Z
	Vector2 Mul(float mul);		// 2D�x�N�g���̒萔�{
	Vector2 Div(float div);

	Vector2 Nomalize();				// 2D�x�N�g���̐��K��
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

	bool CrossPoint(Vector2* vec1_gool, Vector2* vec2_start, Vector2* vec2_gool, Vector2* output);// �����Ɛ����̌�_�����߂�
};
