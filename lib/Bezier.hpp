#ifndef BEZIER_H
#define BEZIER_H

/**
 * \file Bezier.hpp
 * \brief Header de la classe Bezier.
 */

#include <fstream>
#include <vector>
#include <algorithm>
#include "BezierPoint.hpp"

/**
 * \class Bezier Bezier.hpp
 * \author Maxime BRIDE
 * \version 0.1
 * \brief Permet de g�rer des courbes de B�zier.
 * \example simple/main.cpp
 * \example GUI/src/main.cpp
 * \example GUI/src/BezierWindow.cpp
 * \example GUI/src/BezierWindow.hpp
 * \example GUI/src/BezierItem.cpp
 * \example GUI/src/BezierItem.hpp
 */
class Bezier {
	public:
		/**
		 * \brief Structure permettant de repr�senter les limites de la courbe.
		 */
		struct BezierBounds {
			/**
			 * \brief Coin haut gauche des limites.
			 */
			BezierPoint tl;
			
			/**
			 * \brief Coin bas droit des limites.
			 */
			BezierPoint br;
		};
	
		/**
		 * \brief Constructeur par d�faut.
		 */
		Bezier();
		
		/**
		 * \brief Constructeur permettant de sp�cifier une pr�cision.
		 * \param precision La pr�cision.
		 */
		Bezier(int);
		
		/**
		 * \brief Constructeur permettant de sp�cifier une pr�cision.
		 * \param precision La pr�cision.
		 * \param autoUpdate Bool�en g�rant le mode de mise � jour.
		 */
		Bezier(int, bool);
		
		/**
		 * \brief Constructeur permettant de sp�cifier un fichier de points.
		 * \param filename Le nom du fichier de points.
		 */
		Bezier(std::string);
		
		/**
		 * \brief Ajoute un nouveau point de contr�le.
		 * \param pt Le nouveau point de contr�le.
		 */
		void addControlPoint(const BezierPoint&);
		
		/**
		 * \brief Ajoute un nouveau point de contr�le.
		 * \param x La coordonn�e x du point de contr�le.
		 * \param y La coordonn�e y du point de contr�le.
		 */
		void addControlPoint(double, double);
		
		/**
		 * \brief Supprime un point de contr�le.
		 * \param pt Le point de contr�le � supprimer.
		 */
		void removeControlPoint(const BezierPoint&);
		
		/**
		 * \brief Supprime un point de contr�le.
		 * \param x La coordonn�e x du point de contr�le.
		 * \param y La coordonn�e y du point de contr�le.
		 */
		void removeControlPoint(double, double);
		
		/**
		 * \brief Calcule un point de l'approximation de la courbe de B�zier.
		 *        L'algorithme prend en entr�e une liste de points de contr�le
		 *        et la position du point de la courbe � calculer (entre 0 et 1).
		 *        L'algorithme calcule, pour les N points de contr�les, N - 1
		 *        nouveaux points qui sont les barycentres de chaque paire de
		 *        points cons�cutives.
		 *        Pour chaque paire de points, il faut associer un poids pos 
		 *        pour le premier point et 1 - pos pour le second.
		 *        On effectue ces calculs jusqu'� ce qu'il n'y ait plus qu'un
		 *        seul point qui est le point que l'on cherche.
		 *        Il suffit de faire un appel � cet algorithme pour toutes les
		 *        positions de points (0, 1 / M, 2 / M, ..., M - 1 / M, 1) avec
		 *        M le nombre de segments de la courbe (la pr�cision).
		 * \param pts Les points de contr�les.
		 * \param pos L'emplacement du point � calculer.
		 * \return Le point calcul�.
		 */
		BezierPoint deCasteljau(const std::vector<BezierPoint>&, double);

		/**
		 * \brief Calcule les points de l'approximation de la courbe de B�zier.
		 */
		void update();
		
		/**
		 * \brief Renvoie les points de l'appriximation de la courbe de B�zier.
		 * \return Les points de l'appriximation de la courbe de B�zier.
		 */
		const std::vector<BezierPoint>& curvePoints();
		
		/**
		 * \brief Renvoie les points de contr�le de la courbe de B�zier.
		 * \return Les points de contr�le de la courbe de B�zier.
		 */
		const std::vector<BezierPoint>& controlPoints();
		
		/**
		 * \brief Assigne une nouvelle pr�cision.
		 * \param precision La nouvelle pr�cision.
		 */
		void setPrecision(int);
		
		/**
		 * \brief Acc�de � la pr�cision.
		 * \return La pr�cision.
		 */
		int precision();
		
		/**
		 * \brief Assigne une nouvelle valeur pour m_autoUpdate.
		 * \param autoUpdate La nouvelle valeur pour m_autoUpdate.
		 */
		void setAutoUpdate(bool);
		
		/**
		 * \brief Acc�de � la valeur de m_autoUpdate.
		 * \return La valeur de m_autoUpdate.
		 */
		bool autoUpdate();
		
		/**
		 * \brief Retourne les limites de la courbe.
		 * \return Les limites de la courbe.
		 */
		BezierBounds bounds() const;
		
		/**
		 * \brief Indique si la courbe est valide (pr�cision non nulle et plus
		 *        de 2 points de cointr�le).
		 * \return Le bool�en qui indique si la courbe est valide.
		 */
		bool isValid();

	private:
		/**
		 * \brief Met � jour les limites de la courbe.
		 */
		void updateBounds();
	
		/**
		 * \brief Points de l'appriximation de la courbe de B�zier.
		 */
		std::vector<BezierPoint> m_curvePoints;
		
		/**
		 * \brief Points de contr�le de la courbe de B�zier.
		 */
		std::vector<BezierPoint> m_controlPoints;
		
		/**
		 * \brief Limites de la courbe de B�zier.
		 */
		BezierBounds m_bounds;
		
		/**
		 * \brief Pr�cision de la courbe (nombre de segments pour la "courbe").
		 */
		int m_precision;
		
		/**
		 * \brief Indique si l'on doit recalculer les points � chaque changement
		 *        (ajout ou suppression de point de contr�le, changement de 
		 *        pr�cision, ...).
		 */
		bool m_autoUpdate;
};

#endif /* BEZIER_H */
