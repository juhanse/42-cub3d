# 🕹️ Cub3D

Cub3D est un projet **42** inspiré du célèbre jeu *Wolfenstein 3D*.  
L’objectif est d’implémenter un moteur graphique en **raycasting** qui affiche une vue 3D à partir d’une **carte 2D**, le tout en **C**.

---

## 🚀 Fonctionnalités
- Moteur de rendu 3D minimaliste avec **raycasting**.
- Gestion des textures pour murs, sol et plafond.
- Déplacements fluides (avant, arrière, strafe, rotation).
- Parsing robuste des fichiers `.cub` (textures, couleurs, carte).

---

## 🖼️ Lien avec la MiniLibX

Le rendu graphique s’appuie sur **MiniLibX (mlx)**, une petite bibliothèque graphique fournie par 42.  
Elle permet de :
- Créer une fenêtre et gérer les événements clavier/souris.
- Afficher des images (textures, murs, sol/plafond).
- Manipuler les pixels pour le raycasting en temps réel.

> **Remarque** : la `mlx` est déjà incluse/configurée dans le Makefile.

---

## 🛠️ Lancement

Assurez-vous d’avoir **make** et un environnement compatible avec **MiniLibX** (macOS ou Linux avec X11).

```bash
# Compiler
make

# Lancer avec une carte .cub
./cub3d maps/map.cub
```

---

## ⚠️ Avis important

Ce projet est mis en ligne uniquement à des fins de portfolio et de démonstration personnelle.
Il n’a pas vocation à être copié ou utilisé comme solution.
