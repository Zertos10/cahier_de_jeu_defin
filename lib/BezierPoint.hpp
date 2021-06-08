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
 * \brief Permet de gérer les points des courbes de Bézier.
 */
class BezierPoint {
	/**
	 * \brief Surcharge de l'opérateur de flux pour l'affichage.
	 * \param stream Le flux d'affichage.
	 * \param pt Le point à afficher.
	 * \return Le flux d'affichage.
	 */
	friend std::ostream& operator<<(std::ostream& stream, const BezierPoint& pt) {
		stream << pt.toString();
		return stream;
	}

	public:
		/**
		 * \brief Constructeur par défaut.
		 */
		BezierPoint();
		
		/**
		 * \brief Constructeur pour assigner x et y.
		 * \param x La coordonnée x.
		 * \param y La coordonnée y.
		 */
		BezierPoint(double, double);
	
		/**
		 * \brief Constructeur pour assigner x, y et un poids.
		 * \param x La coordonnée x.
		 * \param y La coordonnée y.
		 * \param w Le poids du point.
		 */
		BezierPoint(double, double, double);
		
		/**
		 * \brief Constructeur par recopie.
		 * \param pt Le point à copier.
		 */
		BezierPoint(const BezierPoint&);
		
		/**
		 * \brief Opérateur d'affectation.
		 * \param pt Le point à copier.
		 * \return Le point copié.
		 */
		const BezierPoint& operator=(const BezierPoint&);
		
		/**
		 * \brief Opérateur d'égalité.
		 * \param pt Le point à tester.
		 * \return La résultat de la comparaison.
		 */
		bool operator==(const BezierPoint&);
		
		/**
		 * \brief Renseigne une nouvelle coordonnée x.
		 * \param x La coordonnée x.
		 */
		void setX(double);
		
		/**
		 * \brief Renseigne une nouvelle coordonnée y.
		 * \param y La coordonnée y.
		 */
		void setY(double);
		
		/**
		 * \brief Renseigne un nouveau poids w.
		 * \param w La poids.
		 */
		void setWeight(double);
		
		/**
		 * \brief Accède à la coordonnée x.
		 * \return La coordonnée x.
		 */
		double x() const;
		
		/**
		 * \brief Accède à la coordonnée y.
		 * \return La coordonnée y.
		 */
		double y() const;
		
		/**
		 * \brief Accède au poids w.
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
		 * \brief Représentation du point sous forme de chaîne de caractères.
		 * \return Une chaîne de caractère représentant le point.
		 */
		std::string toString() const;

	private:
		double m_x;
		double m_y;
		double m_w;
};
	
#endif /* BEZIERPOINT_H */
