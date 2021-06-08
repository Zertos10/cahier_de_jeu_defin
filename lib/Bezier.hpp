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
 * \brief Permet de gérer des courbes de Bézier.
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
		 * \brief Structure permettant de représenter les limites de la courbe.
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
		 * \brief Constructeur par défaut.
		 */
		Bezier();
		
		/**
		 * \brief Constructeur permettant de spécifier une précision.
		 * \param precision La précision.
		 */
		Bezier(int);
		
		/**
		 * \brief Constructeur permettant de spécifier une précision.
		 * \param precision La précision.
		 * \param autoUpdate Booléen gérant le mode de mise à jour.
		 */
		Bezier(int, bool);
		
		/**
		 * \brief Constructeur permettant de spécifier un fichier de points.
		 * \param filename Le nom du fichier de points.
		 */
		Bezier(std::string);
		
		/**
		 * \brief Ajoute un nouveau point de contrôle.
		 * \param pt Le nouveau point de contrôle.
		 */
		void addControlPoint(const BezierPoint&);
		
		/**
		 * \brief Ajoute un nouveau point de contrôle.
		 * \param x La coordonnée x du point de contrôle.
		 * \param y La coordonnée y du point de contrôle.
		 */
		void addControlPoint(double, double);
		
		/**
		 * \brief Supprime un point de contrôle.
		 * \param pt Le point de contrôle à supprimer.
		 */
		void removeControlPoint(const BezierPoint&);
		
		/**
		 * \brief Supprime un point de contrôle.
		 * \param x La coordonnée x du point de contrôle.
		 * \param y La coordonnée y du point de contrôle.
		 */
		void removeControlPoint(double, double);
		
		/**
		 * \brief Calcule un point de l'approximation de la courbe de Bézier.
		 *        L'algorithme prend en entrée une liste de points de contrôle
		 *        et la position du point de la courbe à calculer (entre 0 et 1).
		 *        L'algorithme calcule, pour les N points de contrôles, N - 1
		 *        nouveaux points qui sont les barycentres de chaque paire de
		 *        points consécutives.
		 *        Pour chaque paire de points, il faut associer un poids pos 
		 *        pour le premier point et 1 - pos pour le second.
		 *        On effectue ces calculs jusqu'à ce qu'il n'y ait plus qu'un
		 *        seul point qui est le point que l'on cherche.
		 *        Il suffit de faire un appel à cet algorithme pour toutes les
		 *        positions de points (0, 1 / M, 2 / M, ..., M - 1 / M, 1) avec
		 *        M le nombre de segments de la courbe (la précision).
		 * \param pts Les points de contrôles.
		 * \param pos L'emplacement du point à calculer.
		 * \return Le point calculé.
		 */
		BezierPoint deCasteljau(const std::vector<BezierPoint>&, double);

		/**
		 * \brief Calcule les points de l'approximation de la courbe de Bézier.
		 */
		void update();
		
		/**
		 * \brief Renvoie les points de l'appriximation de la courbe de Bézier.
		 * \return Les points de l'appriximation de la courbe de Bézier.
		 */
		const std::vector<BezierPoint>& curvePoints();
		
		/**
		 * \brief Renvoie les points de contrôle de la courbe de Bézier.
		 * \return Les points de contrôle de la courbe de Bézier.
		 */
		const std::vector<BezierPoint>& controlPoints();
		
		/**
		 * \brief Assigne une nouvelle précision.
		 * \param precision La nouvelle précision.
		 */
		void setPrecision(int);
		
		/**
		 * \brief Accède à la précision.
		 * \return La précision.
		 */
		int precision();
		
		/**
		 * \brief Assigne une nouvelle valeur pour m_autoUpdate.
		 * \param autoUpdate La nouvelle valeur pour m_autoUpdate.
		 */
		void setAutoUpdate(bool);
		
		/**
		 * \brief Accède à la valeur de m_autoUpdate.
		 * \return La valeur de m_autoUpdate.
		 */
		bool autoUpdate();
		
		/**
		 * \brief Retourne les limites de la courbe.
		 * \return Les limites de la courbe.
		 */
		BezierBounds bounds() const;
		
		/**
		 * \brief Indique si la courbe est valide (précision non nulle et plus
		 *        de 2 points de cointrôle).
		 * \return Le booléen qui indique si la courbe est valide.
		 */
		bool isValid();

	private:
		/**
		 * \brief Met à jour les limites de la courbe.
		 */
		void updateBounds();
	
		/**
		 * \brief Points de l'appriximation de la courbe de Bézier.
		 */
		std::vector<BezierPoint> m_curvePoints;
		
		/**
		 * \brief Points de contrôle de la courbe de Bézier.
		 */
		std::vector<BezierPoint> m_controlPoints;
		
		/**
		 * \brief Limites de la courbe de Bézier.
		 */
		BezierBounds m_bounds;
		
		/**
		 * \brief Précision de la courbe (nombre de segments pour la "courbe").
		 */
		int m_precision;
		
		/**
		 * \brief Indique si l'on doit recalculer les points à chaque changement
		 *        (ajout ou suppression de point de contrôle, changement de 
		 *        précision, ...).
		 */
		bool m_autoUpdate;
};

#endif /* BEZIER_H */
