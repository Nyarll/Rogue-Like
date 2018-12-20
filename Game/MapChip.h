#pragma once

class MapChip
{
public:
	static const int SIZE;		// �T�C�Y
	static const int OFFSET;	// �I�t�Z�b�g
	static const int PADDING;	// �p�f�B���O

private:
	int gh;				// �O���t�B�b�N�n���h��
	bool isPassable;	// �ʍs�ł��邩�ǂ���

public:
	MapChip(int tex, int rowNum, int colNum, bool is_passable);
	~MapChip();

	void Render(int x, int y, int grid_size)const;
	bool IsPassable()const;
};