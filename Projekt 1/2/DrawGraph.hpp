#pragma once

class DrawGraph
{
private:
	const unsigned int node_number;
	const double x0;
	const double y0;
	const double r0;
public:
	DrawGraph(const unsigned int n, const double r, const double x, const double y);
	void GenerateScript();
};
