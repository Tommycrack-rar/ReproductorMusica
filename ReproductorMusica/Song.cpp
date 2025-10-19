#include "Song.h"
#include <iostream>

// CONSTRUCTOR
Song::Song(const std::string& path, const std::string& title,
           const std::string& artist, const std::string& album)
    : filePath(path), title(title), artist(artist), album(album),
      genre(""), duration("00:00"), year(0), trackNumber(0) {
}

// GETTERS
std::string Song::getFilePath() const { return filePath; }
std::string Song::getTitle() const { return title; }
std::string Song::getArtist() const { return artist; }
std::string Song::getAlbum() const { return album; }
std::string Song::getGenre() const { return genre; }
std::string Song::getDuration() const { return duration; }
int Song::getYear() const { return year; }
int Song::getTrackNumber() const { return trackNumber; }

// SETTERS
void Song::setTitle(const std::string& title) { this->title = title; }
void Song::setArtist(const std::string& artist) { this->artist = artist; }
void Song::setAlbum(const std::string& album) { this->album = album; }
void Song::setGenre(const std::string& genre) { this->genre = genre; }
void Song::setYear(int year) { this->year = year; }
void Song::setTrackNumber(int trackNumber) { this->trackNumber = trackNumber; }
void Song::setDuration(const std::string& duration) { this->duration = duration; }

// CARGAR METADATOS (versión simplificada)
bool Song::loadMetadata() {
    // Si ya tenemos datos básicos, los usamos
    if (!title.empty() && !artist.empty()) {
        return true;
    }

    // Intentar extraer del nombre del archivo como fallback
    if (title.empty()) {
        // Ejemplo: "C:/Music/Queen - Bohemian Rhapsody.mp3" → "Bohemian Rhapsody"
        size_t start = filePath.find_last_of("/\\");
        size_t end = filePath.find_last_of(".");

        if (start != std::string::npos && end != std::string::npos) {
            std::string filename = filePath.substr(start + 1, end - start - 1);

            // Intentar separar artista - título
            size_t separator = filename.find(" - ");
            if (separator != std::string::npos) {
                artist = filename.substr(0, separator);
                title = filename.substr(separator + 3);
            } else {
                title = filename;
            }
        }
    }

    // Si todavía no tenemos artista, usar "Desconocido"
    if (artist.empty()) {
        artist = "Artista Desconocido";
    }

    // Si todavía no tenemos título, usar nombre del archivo
    if (title.empty()) {
        title = "Canción Desconocida";
    }

    return true;
}

// CONVERTIR A STRING
std::string Song::toString() const {
    return artist + " - " + title + " (" + album + ")";
}

// VERIFICAR SI LA CANCIÓN ES VÁLIDA
bool Song::isValid() const {
    return !filePath.empty() && !title.empty() && !artist.empty();
}

// FORMATEAR DURACIÓN (helper privado)
std::string Song::formatDuration(int seconds) const {
    int minutes = seconds / 60;
    int secs = seconds % 60;

    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, secs);
    return std::string(buffer);
}
