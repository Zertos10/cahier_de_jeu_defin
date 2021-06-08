#ifndef BEZIERPOINT_H
#define BEZIERPOINT_H

/**
 * \file BezierPoint.hpp
 * \brief Header de la classe BezierPoint.
 */
 
#include <iostream>
#include <sstream>

/**
 * \class BezierPoint BezierPoint.hpp
 * \author Maxime BRIDE
 * \version 0.1
 * \brief Permet de g�rer les points des courbes de B�zier.
 */
class BezierPoint {
	/**
	 * \brief Surcharge de l'op�rateur de flux pour l'affichage.
	 * \param stream Le flux d'affichage.
	 * \param pt Le point � afficher.
	 * \return Le flux d'affichage.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const BezierPoint& pt) {
		stream << pt.toString();
		return stream;
	}

	public:
		/**
		 * \brief Constructeur par d�faut.
		 */
		BezierPoint();
		
		/**
		 * \brief Constructeur pour assigner x et y.
		 * \param x La coordonn�e x.
		 * \param y La coordonn�e y.
		 */
		BezierPoint(double, double);
	
		/**
		 * \brief Constructeur pour assigner x, y et un poids.
		 * \param x La coordonn�e x.
		 * \param y La coordonn�e y.
		 * \param w Le poids du point.
		 */
		BezierPoint(double, double, double);
		
		/**
		 * \brief Constructeur par recopie.
		 * \param pt Le point � copier.
		 */
		BezierPoint(const BezierPoint&);
		
		/**
		 * \brief Op�rateur d'affectation.
		 * \param pt Le point � copier.
		 * \return Le point copi�.
		 */
		const BezierPoint& operator=(const BezierPoint&);
		
		/**
		 * \brief Op�rateur d'�galit�.
		 * \param pt Le point � tester.
		 * \return La r�sultat de la comparaison.
		 */
		bool operator==(const BezierPoint&);
		
		/**
		 * \brief Renseigne une nouvelle coordonn�e x.
		 * \param x La coordonn�e x.
		 */
		void setX(double);
		
		/**
		 * \brief Renseigne une nouvelle coordonn�e y.
		 * \param y La coordonn�e y.
		 */
		void setY(double);
		
		/**
		 * \brief Renseigne un nouveau poids w.
		 * \param w La poids.
		 */
		void setWeight(double);
		
		/**
		 * \brief Acc�de � la coordonn�e x.
		 * \return La coordonn�e x.
		 */
		double x() const;
		
		/**
		 * \brief Acc�de � la coordonn�e y.
		 * \return La coordonn�e y.
		 */
		double y() const;
		
		/**
		 * \brief Acc�de au poids w.
		 * \return Le poids.
		 */
		double weight() const;
		
		/**
		 * \brief Calcul le points barycentre entre le point courant et un
		 *        autre point.
		 * \return Le point barycentre.
		 */
		const BezierPoint& barycentre(const BezierPoint&);
		
		/**
		 * \brief Repr�sentation du point sous forme de cha�ne de caract�res.
		 * \return Une cha�ne de caract�re repr�sentant le point.
		 */
		std::string toString() const;

	private:
		double m_x;
		double m_y;
		double m_w;
};
	
#endif /* BEZIERPOINT_H */
