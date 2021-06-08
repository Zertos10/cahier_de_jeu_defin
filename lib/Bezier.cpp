/**
 * \file Bezier.cpp
 * \brief Définition de la classe Bezier.
 */

#include "Bezier.hpp"	

Bezier::Bezier() : m_precision(15), m_autoUpdate(true) {
}

Bezier::Bezier(int precision) : m_precision(precision), m_autoUpdate(true) {
}

Bezier::Bezier(int precision, bool autoUpdate) : m_precision(precision),
												 m_autoUpdate(autoUpdate) {
}

Bezier::Bezier(std::string filename) {
	double x, y;
	m_autoUpdate = false;
	m_precision = 15;
	
	std::ifstream f(filename.c_str());
	if(f.is_open()) {
		f >> m_precision;
		while(f >> x >> y) {
			addControlPoint(x, y);
		}
		f.close();
	}
	
	update();
}

void Bezier::addControlPoint(const BezierPoint& pt) {
	m_controlPoints.push_back(pt);
	updateBounds();
	if(m_autoUpdate) update();
}

void Bezier::addControlPoint(double x, double y) {
	addControlPoint(BezierPoint(x, y));
}

void Bezier::removeControlPoint(const BezierPoint& pt) {
	std::vector<BezierPoint>::iterator it;
	it = std::find(m_controlPoints.begin(), m_controlPoints.end(), pt);
	if(it != m_controlPoints.end()) {
		m_controlPoints.erase(it);
	}
	updateBounds();
	if(m_autoUpdate) update();
}

void Bezier::removeControlPoint(double x, double y) {
	removeControlPoint(BezierPoint(x, y));
}

BezierPoint Bezier::deCasteljau(const std::vector<BezierPoint>& pts,
								double pos) {
	if(pts.size() == 1) return pts[0];
	std::vector<BezierPoint> pts2;
	for(unsigned int i = 0; i < pts.size() - 1; i++) {
		BezierPoint p1(pts[i].x(), pts[i].y(), 1 - pos);
		BezierPoint p2(pts[i + 1].x(), pts[i + 1].y(), pos);
		pts2.push_back(p1.barycentre(p2));
	}
	return deCasteljau(pts2, pos);
}

void Bezier::update() {
	if(isValid()) {
		m_curvePoints.clear();
		for(int i = 0; i <= m_precision; i++) {
			double pos = i / (double)m_precision;
			m_curvePoints.push_back(deCasteljau(m_controlPoints, pos));
		}
	}
}

const std::vector<BezierPoint>& Bezier::curvePoints() {
	return m_curvePoints;
}

const std::vector<BezierPoint>& Bezier::controlPoints() {
	return m_controlPoints;
}
		
void Bezier::setPrecision(int precision) {
	m_precision = precision;
	if(m_autoUpdate) update();
}
		
int Bezier::precision() {
	return m_precision;
}

void Bezier::setAutoUpdate(bool autoUpdate) {
	m_autoUpdate = autoUpdate;
}

bool Bezier::autoUpdate() {
	return m_autoUpdate;
}

Bezier::BezierBounds Bezier::bounds() const {
	return m_bounds;
}

void Bezier::updateBounds() {
	double minX = m_controlPoints[0].x();
	double minY = m_controlPoints[0].y();
	double maxX = m_controlPoints[0].x();
	double maxY = m_controlPoints[0].y();
	
	for(unsigned int i = 0; i < m_controlPoints.size(); i++) {
		if(m_controlPoints[i].x() < minX) {
			minX = m_controlPoints[i].x();
		}
		if(m_controlPoints[i].x() > maxX) {
			maxX = m_controlPoints[i].x();
		}
		if(m_controlPoints[i].y() < minY) {
			minY = m_controlPoints[i].y();
		}
		if(m_controlPoints[i].y() > maxY) {
			maxY = m_controlPoints[i].y();
		}
	}
	
	m_bounds.tl.setX(minX);
	m_bounds.tl.setY(minY);
	m_bounds.br.setX(maxX);
	m_bounds.br.setY(maxY);
}

bool Bezier::isValid() {
	return m_precision > 0 && m_controlPoints.size() > 2;
}