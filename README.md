*This project has been created as part of the 42 curriculum by abuet.*

# FdF — Fil de Fer

## Description

FdF (Fil de Fer) est un projet du cursus 42 qui consiste à représenter un relief en 3D à partir d'une carte de points en utilisant une projection isométrique. Chaque point de la carte possède une coordonnée Z (altitude) et une couleur optionnelle. Le programme relie ces points par des segments de droites pour former un rendu "fil de fer" (wireframe).

L'objectif est de se familiariser avec la gestion graphique bas niveau via la MiniLibX, les algorithmes de rendu (DDA), les projections 3D et la gestion des événements clavier/fenêtre.

---

## Instructions

### Compilation

```bash
make

make re

make clean

make fclean
```

### Exécution

```bash
./fdf <chemin_vers_carte.fdf>
```

**Exemple :**
```bash
./fdf test_maps/42.fdf
./fdf test_maps/elem.fdf
```

### Format de la carte `.fdf`

Chaque ligne de la carte représente une rangée de points. Chaque point est une valeur entière (l'altitude Z), avec une couleur optionnelle en hexadécimal séparée par une virgule :

```
0 0 0 0
0,0xFF0000 5,0x00FF00 0
0 0 0 0
```

---

## Contrôles

| Touche | Action |
|--------|--------|
| `↑` / `↓` | Zoom avant / arrière |
| `←` / `→` | Translation horizontale |
| `W` / `S` | Rotation (inclinaison) |
| `ESC` | Quitter proprement |
| Croix rouge | Fermer la fenêtre |

---

## Fonctionnalités

- Projection isométrique configurable (angle modifiable)
- Zoom et translation de la carte
- Rotation de la vue
- Gestion des couleurs par point
- Adaptation dynamique à la taille de la carte
- Fermeture propre (libération mémoire, destruction des ressources MiniLibX)
- Compatible macOS et Linux

---

## Resources

### Documentation officielle
- [MiniLibX Documentation (42)](https://harm-smits.github.io/42docs/libs/minilibx)
- [Algorithme DDA — Wikipedia](https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_droite_de_Bresenham)
- [Projection isométrique — Wikipedia](https://fr.wikipedia.org/wiki/Perspective_isom%C3%A9trique)

### Références utiles
- [Guide MiniLibX Linux](https://github.com/42Paris/minilibx-linux)
- [Guide MiniLibX macOS](https://github.com/42Paris/minilibx_mms_v1)

### Utilisation de l'IA

L'IA a été utilisée comme outil d'aide au développement sur les points suivants :

- **Débogage** : identification de bugs (double définition de struct, mauvaise signature de callbacks MiniLibX, division entière produisant `size_square = 0`)
- **Algorithme DDA** : explication et correction de l'algorithme pour itérer sur l'axe dominant et éviter les trous dans les lignes
- **Projection isométrique** : formules de rotation et de translation
