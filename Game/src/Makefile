-include dependencies.txt

CC = g++
CXXFLAGS = -O3 -std=c++0x -Wall -g
LDFLAGS =
APPNAME = ShipDuel
SOURCES = $(wildcard *.cpp)

all: $(APPNAME)
clean:
	find . -name '*.o' -exec rm {} \;
.PHONY: all clean

sdl_cflags := $(shell pkg-config --cflags sdl2 SDL2_mixer SDL2_ttf SDL2_image)
sdl_libs := $(shell pkg-config --libs sdl2 SDL2_mixer SDL2_ttf SDL2_image)
override CXXFLAGS += $(sdl_cflags)
override LIBS += $(sdl_libs)

depend:
	$(CC) -M Manager/AudioManager.cpp Audio/AudioTrack.cpp Audio/AudioChunk.cpp Debug/Debug.cpp GameObject/Asteroid.cpp Manager/AsteroidFactory.cpp GameObject/Base.cpp GameObject/Bullet.cpp Rendering/Camera.cpp Manager/CollisionManager.cpp Manager/Constants.cpp GameState/Credits.cpp GameObject/Flag.cpp Game.cpp GameState/GameOver.cpp GameState/GameState.cpp GUI/InGameUI.cpp Manager/JoypadManager.cpp GameState/MainGame.cpp GameState/MainLevel.cpp GameState/MainMenu.cpp GameState/MenuGameState.cpp GUI/MessageBox.cpp Manager/MessageBoxFactory.cpp GameObject/Player.cpp Manager/PlayerManager.cpp GameState/SelectPlayers.cpp Rendering/Sprite.cpp Manager/TextManager.cpp Rendering/Tile.cpp Rendering/TileMap.cpp Manager/TileMapManager.cpp Manager/TimeManager.cpp Manager/Utils.cpp Math/Vector2.cpp > dependencies.txt

$(APPNAME): Manager/AudioManager.o Audio/AudioTrack.o Audio/AudioChunk.o Debug/Debug.o GameObject/Asteroid.o Manager/AsteroidFactory.o GameObject/Base.o GameObject/Bullet.o Rendering/Camera.o Manager/CollisionManager.o Manager/Constants.o GameState/Credits.o GameObject/Flag.o Game.o GameState/GameOver.o GameState/GameState.o GUI/InGameUI.o Manager/JoypadManager.o GameState/MainGame.o GameState/MainLevel.o GameState/MainMenu.o GameState/MenuGameState.o GUI/MessageBox.o Manager/MessageBoxFactory.o GameObject/Player.o Manager/PlayerManager.o GameState/SelectPlayers.o Rendering/Sprite.o Manager/TextManager.o Rendering/Tile.o Rendering/TileMap.o Manager/TileMapManager.o Manager/TimeManager.o Manager/Utils.o Math/Vector2.o
	$(CC) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
