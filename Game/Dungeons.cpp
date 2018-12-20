#include "Dungeons.h"

int RL_Create(DngMap_RL* dng, MapData_RL maprl[][MY], Mob_RL* mob) {

	for (int i = 0; i < RL_MOB_C; i++) {
		mob[i].id = 0;
		mob[i].x = 0;
		mob[i].y = 0;
		mob[i].s = 1;
	}

	RL_Make(dng, maprl);

	for (int i = 0; i < RL_MOB_C; i++) {
		RL_MakeMob(dng, maprl, mob, i);
	}

	return 0;
}

int RL_Make(DngMap_RL* dng, MapData_RL maprl[][MY])
{
	//������
	for (int i = 0; i < MX; i++) {
		for (int j = 0; j < MY; j++) {
			maprl[i][j].mapData = 1;
		}
	}

	dng->mapDivCount = dng->divCountMin + GetRand(dng->divCountRand); //�}�b�v�̋敪���� (�����̌�) 0~n�܂ł̕���ID
	if (dng->mapDivCount > 7) return -1;

	for (int i = 0; i < dng->mapDivCount; i++) {
		dng->mapRoomArea[i] = 0;
	}
	dng->mapTotalArea = 0;
	dng->mapRoomCount = 0;

	dng->mapDiv[0][0] = (MX - 1); //�}�b�v�̋敪�������T�C�YX�I�_ (�}�b�v�̑傫��X��)
	dng->mapDiv[0][1] = (MY - 1); //�}�b�v�̋敪�������T�C�YY�I�_ (�}�b�v�̑傫��Y��)
	dng->mapDiv[0][2] = 1; //�}�b�v�̋敪�������T�C�YX�n�_ (�}�b�v�̑傫��X��)
	dng->mapDiv[0][3] = 1; //�}�b�v�̋敪�������T�C�YY�n�_ (�}�b�v�̑傫��Y��)

	dng->mapRoad[0][0] = 255;
	dng->mapRoad[0][1] = 255;

	/*�}�b�v���敪�����Ă�������(���𕪊����鏈��)*/
	int divAfter;
	int count; //(0:X, 1:Y) X���ŕ����邩Y���ŕ����邩���߂�

	for (int i = 1; i < dng->mapDivCount; i++) {

		//���܂ō�����敪���������_���Ɏw��(�w�肵����������ɋ敪������)
		divAfter = GetRand(i - 1);

		//�w�肵������X��Y�̒����ɂ���āA����������������߂�(�����ق��𕪊�����)
		if (dng->mapDiv[divAfter][0] - dng->mapDiv[divAfter][2] > dng->mapDiv[divAfter][1] - dng->mapDiv[divAfter][3]) count = RL_COUNT_X;
		else count = RL_COUNT_Y;

		if (dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2] < dng->divCountRand * 2 + 8) {
			int k = 0;
			for (int j = 1; j < dng->mapDivCount; j++) {
				if (dng->mapDiv[j][0] - dng->mapDiv[j][2] > k) {
					k = dng->mapDiv[j][0] - dng->mapDiv[j][2];
					divAfter = j;
					count = RL_COUNT_X;
				}
				if (dng->mapDiv[j][1] - dng->mapDiv[j][3] > k) {
					k = dng->mapDiv[j][1] - dng->mapDiv[j][3];
					divAfter = j;
					count = RL_COUNT_Y;
				}
			}
		}

		dng->mapRoad[i][0] = divAfter;
		dng->mapRoad[i][1] = count;

		for (int j = 1; j < i; j++)
			if (dng->mapRoad[j][0] == divAfter) dng->mapRoad[j][0] = i;

		//count���̐ݒ�
		dng->mapDiv[i][count] = dng->mapDiv[divAfter][count + 2] + (dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2]) / 3 + GetRand((dng->mapDiv[divAfter][count] - dng->mapDiv[divAfter][count + 2]) / 3); //0.���̉E�[(iR)�̍��W(divAfter*R/3~2divAfter*R/3)
		dng->mapDiv[i][count + 2] = dng->mapDiv[divAfter][count + 2]; //0.���̍��[(iL)�̍��W(divAfterL)
		dng->mapDiv[divAfter][count + 2] = dng->mapDiv[i][count]; //divAfter���̍��[(divAfterL)�̍��W(iR)

																  //count�Ƃ͋t�̎��̐ݒ�
		dng->mapDiv[i][abs(count - 1)] = dng->mapDiv[divAfter][abs(count - 1)]; //���̉E�[(iR)�̍��W(divAfterR)
		dng->mapDiv[i][abs(count - 1) + 2] = dng->mapDiv[divAfter][abs(count - 1) + 2]; //���̍��[(iL)�̍��W(divAfterL)
	}

	/*�����𐶐����鏈��*/
	for (int i = 0; i < dng->mapDivCount; i++) {//�敪��
		dng->mapRoomPlayer[i] = 0;//�v���C���[�N��������
		dng->mapRoom[i][2] = dng->mapDiv[i][2]; //�敪��X�n�_���}�b�vX�n�_�֑��
		dng->mapRoom[i][3] = dng->mapDiv[i][3]; //�敪��Y�n�_���}�b�vY�n�_�֑��

												//X���W�̕����̒������w��
		dng->mapRoom[i][0] = dng->mapDiv[i][2] + dng->divCountRand + GetRand(dng->roomLengthRandX);
		if (dng->mapDiv[i][0] - dng->mapDiv[i][2] < dng->mapRoom[i][0] - dng->mapRoom[i][2] + 5) {
			dng->mapRoom[i][0] = dng->mapDiv[i][0] - 4;
			if (dng->mapDiv[i][0] - dng->mapDiv[i][2] < dng->mapRoom[i][0] - dng->mapRoom[i][2] + 5) {
				dng->mapRoom[i][0] = dng->mapDiv[i][2] + 1;
			}
		}

		dng->mapRoom[i][1] = dng->mapDiv[i][3] + dng->roomLengthMinY + GetRand(dng->roomLengthRandY);
		if (dng->mapDiv[i][1] - dng->mapDiv[i][3] < dng->mapRoom[i][1] - dng->mapRoom[i][3] + 5) {
			dng->mapRoom[i][1] = dng->mapDiv[i][1] - 4;
			if (dng->mapDiv[i][1] - dng->mapDiv[i][3] < dng->mapRoom[i][1] - dng->mapRoom[i][3] + 5) {
				dng->mapRoom[i][1] = dng->mapDiv[i][3] + 1;
			}
		}

		if (dng->mapRoom[i][0] - dng->mapDiv[i][2] <= 1 || dng->mapRoom[i][1] - dng->mapDiv[i][3] <= 1) {
			dng->mapRoom[i][0] = dng->mapDiv[i][2] + 1;
			dng->mapRoom[i][1] = dng->mapDiv[i][3] + 1;
		}
		int l = GetRand(dng->mapDiv[i][0] - dng->mapRoom[i][0] - 5) + 2;
		int m = GetRand(dng->mapDiv[i][1] - dng->mapRoom[i][1] - 5) + 2;
		dng->mapRoom[i][0] += l;
		dng->mapRoom[i][2] += l;
		dng->mapRoom[i][1] += m;
		dng->mapRoom[i][3] += m;

		for (int j = dng->mapRoom[i][2]; j < dng->mapRoom[i][0]; j++) {
			for (int k = dng->mapRoom[i][3]; k < dng->mapRoom[i][1]; k++) {
				maprl[j][k].mapData = 0;
				dng->mapRoomArea[i]++;
			}
		}

		if (dng->mapRoomArea[i] > 1) {
			dng->mapRoom2[dng->mapRoomCount] = i;
			dng->mapRoomCount++;
			dng->mapTotalArea += dng->mapRoomArea[i];
		}

	}




	/*�ʘH�𐶐����鏈��*/
	/*�ʘH�͂Q�����Ԃׂ̍����̂��Ƃ��w���B
	�ʘH����邽�߂ɂQ���������ꂼ��O(Before)�ƌ�(After)�ŕ�����B
	for���őS�Ă̕������`�F�b�N���A�O��̕������q���ʘH�����B
	�܂��A�O�̒ʘH�����A���Ɍ�̒ʘH�����B
	�Ō�ɑO�ƌ�̒ʘH���q����B
	*/
	int roomAfter;
	for (int roomBefore = 0; roomBefore < dng->mapDivCount; roomBefore++) {
		roomAfter = dng->mapRoad[roomBefore][0];

		//X���W�̒ʘH
		switch (dng->mapRoad[roomBefore][1]) {
		case RL_COUNT_X:
			dng->mapRoad[roomBefore][2] = GetRand(dng->mapRoom[roomBefore][1] - dng->mapRoom[roomBefore][3] - 2); //�O���̒ʘH�̈ʒu
			dng->mapRoad[roomBefore][3] = GetRand(dng->mapRoom[roomAfter][1] - dng->mapRoom[roomAfter][3] - 2); //�㑤�̒ʘH�̈ʒu
			//�O�̒ʘH
			for (int j = dng->mapRoom[roomBefore][0]; j < dng->mapDiv[roomBefore][0]; j++)
				maprl[j][dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���

			 //��̒ʘH
			for (int j = dng->mapDiv[roomAfter][2]; j < dng->mapRoom[roomAfter][2]; j++)
				maprl[j][dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���

			//�ʘH���Ȃ�
			for (int j = dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]; j <= dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]; j++)
				maprl[dng->mapDiv[roomBefore][0]][j].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ��� 2����5(�ォ�牺)
			for (int j = dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][3]; j <= dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][3]; j++)
				maprl[dng->mapDiv[roomBefore][0]][j].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ��� 5����2(�������)
			break;

		case RL_COUNT_Y:
			dng->mapRoad[roomBefore][2] = GetRand(dng->mapRoom[roomBefore][0] - dng->mapRoom[roomBefore][2] - 2); //�O���̒ʘH�̈ʒu
			dng->mapRoad[roomBefore][3] = GetRand(dng->mapRoom[roomAfter][0] - dng->mapRoom[roomAfter][2] - 2); //�㑤�̒ʘH�̈ʒu
																												//�O�̒ʘH
			for (int j = dng->mapRoom[roomBefore][1]; j < dng->mapDiv[roomBefore][1]; j++)
				maprl[dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]][j].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���

																								 //��̒ʘH
			for (int j = dng->mapDiv[roomAfter][3]; j < dng->mapRoom[roomAfter][3]; j++)
				maprl[dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]][j].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���

																								//�ʘH���Ȃ�
			for (int j = dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]; j <= dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]; j++)
				maprl[j][dng->mapDiv[roomBefore][1]].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���
			for (int j = dng->mapRoad[roomBefore][3] + dng->mapRoom[roomAfter][2]; j <= dng->mapRoad[roomBefore][2] + dng->mapRoom[roomBefore][2]; j++)
				maprl[j][dng->mapDiv[roomBefore][1]].mapData = 0; //�ʘH���}�b�v�`�b�v�ɐ���
			break;
		}

	}

	//�G���[�`�F�b�N
	if (!dng->mapDivCount)return -1;
	if (dng->mapTotalArea < 5)return -1;

	return 0;
}

int RL_MakeMob(DngMap_RL* dngMap, MapData_RL maprl[][MY], Mob_RL* mob, int id)
{

	//�v���C���[��ݒu����
	int a = dngMap->mapRoom2[GetRand(dngMap->mapRoomCount - 1)]; //�}�b�v��̕����������_���Ɏw�肷��
	int b = GetRand(dngMap->mapRoom[a][0] - dngMap->mapRoom[a][2] - 1); //�}�b�v��X���W�̒����̒����烉���_���Ɏw��
	int c = GetRand(dngMap->mapRoom[a][1] - dngMap->mapRoom[a][3] - 1); //�}�b�v��Y���W�̒����̒����烉���_���Ɏw��

	mob[id].x = dngMap->mapRoom[a][2] + b;
	mob[id].y = dngMap->mapRoom[a][3] + c;

	if (!id) dngMap->mapRoomPlayer[a] = 1; //�����Ƀv���C���[�N��

	mob[id].id = 1;

	//����mob�Əd�Ȃ��Ă��������
	for (int i = 0; i < RL_MOB_C; i++) {
		if (id != i && mob[i].id && mob[id].x == mob[i].x && mob[id].y == mob[i].y) {

			mob[id].id = 0;
			break;

		}
	}


	return 0;
}

