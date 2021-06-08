/**
 * \file BezierPoint.cpp
 * \brief Définition de la classe BezierPoint.
 */

#include "BezierPoint.hpp"	

BezierPoint::BezierPoint() : m_x(0), m_y(0), m_w(0) {
}

BezierPoint::BezierPoint(double x, double y) : m_x(x), m_y(y), m_w(0) {
}
	
BezierPoint::BezierPoint(double x, double y, double w) : m_x(x), m_y(y),
														 m_w(w) {
}
		
BezierPoint::BezierPoint(const BezierPoint& pt) : m_x(pt.m_x), m_y(pt.m_y),
												  m_w(pt.m_w) {
}
		
const BezierPoint& BezierPoint::operator=(const BezierPoint& pt) {
	m_x = pt.m_x;
	m_y = pt.m_y;
	m_w = pt.m_w;
	return *this;
}

bool BezierPoint::operator==(const BezierPoint& pt) {
	return m_x == pt.m_x && m_y == pt.m_y && m_w == pt.m_w;
}

void BezierPoint::setX(double x) {
	m_x = x;
}

void BezierPoint::setY(double y) {
	m_y = y;
}

void BezierPoint::setWeight(double w) {
	m_w = w;
}

double BezierPoint::x() const {
	return m_x;
}

double BezierPoint::y() const {
	return m_y;
}

double BezierPoint::weight() const {
	return m_w;
}

//http://fr.wikibooks.org/wiki/Manuel_de_géométrie_vectorielle/Coordonnées_du_barycentre
const BezierPoint& BezierPoint::barycentre(const BezierPoint& pt) {
	BezierPoint* res = new BezierPoint();
	if(m_w + pt.m_w != 0) {
		res->setX((m_w * m_x + pt.m_w * pt.m_x) / (m_w + pt.m_w));
		res->setY((m_w * m_y + pt.m_w * pt.m_y) / (m_w + pt.m_w));
	}
	return *res;
}

std::string BezierPoint::toString() const {
	std::ostringstream oss;
	oss << m_x << " " << m_y << " " /*<< m_w*/;
	return oss.str();
}
