#include "Song.h.h"
#ifndef SONG_H
#define SONG_H

#include <string>

class Song {
private:
    std::string filePath;    // Ruta completa del archivo
    std::string title;       // T�tulo de la canci�n
    std::string artist;      // Artista
    std::string album;       // �lbum
    std::string genre;       // G�nero musical
    std::string duration;    // Duraci�n en formato "mm:ss"
    int year;               // A�o de lanzamiento
    int trackNumber;        // N�mero de pista

public:
    // Constructor
    Song(const std::string& path = "",
         const std::string& title = "",
         const std::string& artist = "",
         const std::string& album = "");

    // Getters
    std::string getFilePath() const;
    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getGenre() const;
    std::string getDuration() const;
    int getYear() const;
    int getTrackNumber() const;

    // Setters
    void setTitle(const std::string& title);
    void setArtist(const std::string& artist);
    void setAlbum(const std::string& album);
    void setGenre(const std::string& genre);
    void setYear(int year);
    void setTrackNumber(int trackNumber);
    void setDuration(const std::string& duration);

    // M�todos principales
    bool loadMetadata();
    std::string toString() const;
    bool isValid() const;

private:
    std::string formatDuration(int seconds) const;
};

#endif

