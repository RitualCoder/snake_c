# Snake SDL2

Jeu Snake en C avec SDL2, SDL2_image et SDL2_ttf, support High-DPI, menu, écran Game Over, et déplacements case-par-case.

![Snake Game](/assets/images/screen-game.png)

## Fonctionnalités

- Menu avec bouton Play
- Jeu case-par-case (pas d’interpolation)
- Textures pour :
  • Tête (↑ → ↓ ←)
  • Corps droit (horizontal/vertical)
  • Coins (4 orientations)
  • Queue (↑ → ↓ ←)
  • Pomme
- Écran Game Over avec bouton Restart
- Support High-DPI via taille logique
- Configuration simple : nombre de cases et taille des tiles modifiables dans `include/game.h`

## Prérequis

- Compilateur C (gcc, clang)
- SDL2, SDL2_image, SDL2_ttf (et SDL2_gfx selon l’exemple)
  Exemple macOS (Homebrew) :

  ```bash
  brew install sdl2 sdl2_image sdl2_ttf sdl2_gfx
  ```

  Exemple Debian/Ubuntu :

  ```bash
  sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-gfx-dev
  ```

- Git (optionnel)

## Structure du projet

```
project/
  assets/
    fonts/
      Verdana.ttf
    images/
      apple.png
      head_up.png
      head_right.png
      head_down.png
      head_left.png
      body_horizontal.png
      body_vertical.png
      body_bottomleft.png
      body_topleft.png
      body_topright.png
      body_bottomright.png
      tail_up.png
      tail_right.png
      tail_down.png
      tail_left.png
  include/
    apple.h
    game.h
    input.h
    render.h
    sdl_utils.h
    snake.h
    view.h
  src/
    apple.c
    game.c
    input.c
    render.c
    sdl_utils.c
    snake.c
    view.c
  Makefile
  README.txt
```

## Installation

1. Cloner le dépôt :

   ```bash
   git clone https://github.com/RitualCoder/snake_c.git
   cd snake_c
   ```

2. Vérifier que SDL2, SDL2_image et SDL2_ttf sont installés (voir Prérequis).

## Compilation

Dans la racine du projet :

```bash
make
```

Le binaire `snake` sera généré.

## Lancement

```bash
./snake
```

- Menu : cliquez sur **Play** ou appuyez sur **Entrée**
- Gameplay : flèches directionnelles pour diriger le serpent
- Game Over : bouton **Restart** ou touche **R**/**Entrée** pour rejouer
- **Échap** pour quitter

## Configuration

Modifier `include/game.h` :

```c
#define GRID_W    32    // nombre de colonnes
#define GRID_H    24    // nombre de lignes
#define TILE_SIZE 20    // pixels logiques par case
```

## High-DPI

Activé par défaut : SDL adapte l’échelle si nécessaire.

## Assets

- **Fonts** : placer `Verdana.ttf` dans `assets/fonts/`
- **Images** : placer les PNG dans `assets/images/` avec les noms listés

## Nettoyage

```bash
make clean
```

## Licence

MIT © Ton Nom ([https://github.com/ton-utilisateur](https://github.com/ton-utilisateur))
