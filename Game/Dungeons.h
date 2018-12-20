#pragma once

const int MX = (64); //�}�b�v�c�T�C�Y
const int MY = (32); //�}�b�v���T�C�Y
#define RL_COUNT_X (0)
#define RL_COUNT_Y (1)

#define RL_MOB_C 20

struct Mob_RL
{

	unsigned char x = 0;

	unsigned char y = 0;

	unsigned char s = 1;

	unsigned char id = 0;
};

struct System_RL
{
	int turn = 0;
};

struct DngMap_RL
{

	//��������镔���̐� (���m�Ɍ����Ɛ����������̐�)
	unsigned char divCountMin = 5; //�}�b�v�̋敪���ŏ���
	unsigned char divCountRand = 4; //�}�b�v�̋敪�������Z

									//��������镔���̃T�C�Y
	unsigned char roomLengthMinX = 5; //������X���W�̍ŏ��T�C�Y
	unsigned char roomLengthMinY = 5; //������Y���W�̍ŏ��T�C�Y
	unsigned char roomLengthRandX = 2; //������X���W�̃T�C�Y���Z
	unsigned char roomLengthRandY = 2; //������Y���W�̃T�C�Y���Z

	unsigned char mapDivCount; //�}�b�v�̋敪���� (�����̌�) 0~n�܂ł̕���ID
	unsigned char mapDiv[8][4] = { 0 }; //�}�b�v�̋�� [����ID][X�I�_ , Y�I�_ , X�n�_ , Y�n�_]

	unsigned char mapRoomCount = 0; //������
	unsigned char mapRoom2[8] = { 0 }; //������ID
	unsigned char mapRoom[8][4] = { 0 }; //�}�b�v�̕��� [����ID][X�I�_ , Y�I�_ , X�n�_ , Y�n�_]
	unsigned char mapRoad[8][4] = { 0 }; //�}�b�v�̓� [����ID(�O)][�q�����̕���ID(��) , (0.X���W , 1.Y���W) , (�O)���̒ʘH�̈ʒu , (��)���̒ʘH�̈ʒu]
	unsigned char mapRoomPlayer[8] = { 0 };
	unsigned char mapRoomArea[8] = { 0 }; //�����̖ʐ�
	unsigned char mapTotalArea = 0; //�����̑��ʐ�
};

struct MapData_RL
{
	unsigned short mapData = 1; //�}�b�v
};

int RL_Create(DngMap_RL* dngMap, MapData_RL maprl[][MY], Mob_RL* mob);

int RL_Make(DngMap_RL* dng, MapData_RL maprl[][MY]);

int RL_MakeMob(DngMap_RL* dngMap, MapData_RL maprl[][MY], Mob_RL* mob, int id);