#pragma once

// A star

#ifndef __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__
#define __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__

#include <vector>
#include <functional>
#include <set>

namespace AStar
{
	struct Vec2int
	{
		int x, y;

		bool operator == (const Vec2int& coordinates_);
	};

	using uint = unsigned int;
	using HeuristicFunction = std::function<uint(Vec2int, Vec2int)>;
	using CoordinateList = std::vector<Vec2int>;

	struct Node
	{
		uint G, H;
		Vec2int coordinates;
		Node *parent;

		Node(Vec2int coord_, Node *parent_ = nullptr);
		uint getScore();
	};

	using NodeSet = std::set<Node*>;

	class Generator
	{
		bool detectCollision(Vec2int coordinates_);
		Node* findNodeOnList(NodeSet& nodes_, Vec2int coordinates_);
		void releaseNodes(NodeSet& nodes_);

	public:
		Generator();

		// <���[���h�T�C�Y�ݒ�>
		void setWorldSize(Vec2int worldSize_);
		// <�΂߈ړ����邩�ǂ���>
		void setDiagonalMovement(bool enable_);
		// <�q���[���X�e�B�b�N�̐ݒ�>
		void setHeuristic(HeuristicFunction heuristic_);
		// <source_ ���� target_ �܂ł̍ŒZ���[�g>
		CoordinateList findPath(Vec2int source_, Vec2int target_);

		// <�ǂ̓o�^>
		void addCollision(Vec2int coordinates_);
		// <�ǂ̖Y�p>
		void removeCollision(Vec2int coordinates_);
		// <�ǑS����>
		void clearCollisions();

	private:
		HeuristicFunction heuristic;
		CoordinateList direction, walls;
		Vec2int worldSize;
		uint directions;
	};

	class Heuristic
	{
		static Vec2int getDelta(Vec2int source_, Vec2int target_);

	public:
		static uint manhattan(Vec2int source_, Vec2int target_);
		static uint euclidean(Vec2int source_, Vec2int target_);
		static uint octagonal(Vec2int source_, Vec2int target_);
	};
}

#endif