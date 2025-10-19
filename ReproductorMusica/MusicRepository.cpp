#include "MusicRepository.h"
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <cstring>

namespace fs = std::filesystem;

// CONSTRUCTOR
MusicRepository::MusicRepository()
    : capacidad(20), numCanciones(0), cancionActual(-1), libraryPath("") {
    canciones = new Song[capacidad];
}

// DESTRUCTOR
MusicRepository::~MusicRepository() {
    delete[] canciones;
}

// CONSTRUCTOR DE COPIA
MusicRepository::MusicRepository(const MusicRepository& otro)
: capacidad(otro.capacidad), numCanciones(otro.numCanciones),
      cancionActual(otro.cancionActual), libraryPath(otro.libraryPath) {
    //el otro. es para decir que el nuevo va a tener la misma cantidad
    canciones = new Song[capacidad];
    for (int i = 0; i < numCanciones; i++) {
        canciones[i] = otro.canciones[i];
    }
}

// OPERADOR DE ASIGNACI�N
MusicRepository& MusicRepository::operator=(const MusicRepository& otro) {
    if (this == &otro) {
        return *this;
    }

    delete[] canciones;

    capacidad = otro.capacidad;
    numCanciones = otro.numCanciones;
    cancionActual = otro.cancionActual;
    libraryPath = otro.libraryPath;

    canciones = new Song[capacidad];
    for (int i = 0; i < numCanciones; i++) {
        canciones[i] = otro.canciones[i];
    }

    return *this;
}

// REDIMENSIONAR ARREGLO
void MusicRepository::redimensionar(int nuevaCapacidad) {
    if (nuevaCapacidad <= capacidad) {
        return;
    }

    Song* nuevoArreglo = new Song[nuevaCapacidad];

    for (int i = 0; i < numCanciones; i++) {
        nuevoArreglo[i] = canciones[i];
    }

    delete[] canciones;
    canciones = nuevoArreglo;
    capacidad = nuevaCapacidad;
}

// GESTI�N DE BIBLIOTECA
void MusicRepository::setLibraryPath(const std::string& path) {
    libraryPath = path;
}

std::string MusicRepository::getLibraryPath() const {
    return libraryPath;
}

bool MusicRepository::scanDirectory(const std::string& directory) {
    std::string path = directory.empty() ? libraryPath : directory;

    if (path.empty()) {
        return false;
    }

    try {
        int cancionesAgregadas = 0;

        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::string extension = entry.path().extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                if (extension == ".mp3" || extension == ".wav" ||
                    extension == ".ogg" || extension == ".flac") {

                    Song nuevaCancion(entry.path().string());
                    if (nuevaCancion.loadMetadata()) {
                        agregarCancion(nuevaCancion);
                        cancionesAgregadas++;
                    }
                }
            }
        }

        return cancionesAgregadas > 0;

    } catch (const fs::filesystem_error& ex) {
        return false;
    }
}

void MusicRepository::agregarCancion(const Song& cancion) {
    if (numCanciones >= capacidad) {
        redimensionar(capacidad * 2);
    }

    canciones[numCanciones] = cancion;
    numCanciones++;

    if (cancionActual == -1 && numCanciones > 0) {
        cancionActual = 0;
    }
}

bool MusicRepository::eliminarCancion(int index) {
    if (index < 0 || index >= numCanciones) {
        return false;
    }

    for (int i = index; i < numCanciones - 1; i++) {
        canciones[i] = canciones[i + 1];
    }

    numCanciones--;

    if (cancionActual >= numCanciones) {
        cancionActual = numCanciones - 1;
    }
    if (numCanciones == 0) {
        cancionActual = -1;
    }

    return true;
}

void MusicRepository::limpiarRepository() {
    delete[] canciones;
    capacidad = 20;
    numCanciones = 0;
    cancionActual = -1;
    canciones = new Song[capacidad];
}

// NAVEGACI�N
Song* MusicRepository::getCurrentSong() {
    if (cancionActual >= 0 && cancionActual < numCanciones) {
        return &canciones[cancionActual];
    }
    return nullptr;
}

int MusicRepository::getx() {
    if (numCanciones == 0) {
        return -1;
    }
    cancionActual = (cancionActual + 1) % numCanciones;
    return cancionActual;
}

int MusicRepository::getPreviousIndex() {
    if (numCanciones == 0) {
        return -1;
    }
    cancionActual = (cancionActual - 1 + numCanciones) % numCanciones;
    return cancionActual;
}

void MusicRepository::setCurrentIndex(int index) {
    if (index >= 0 && index < numCanciones) {
        cancionActual = index;
    }
}

int MusicRepository::getCurrentIndex() const {
    return cancionActual;
}

// INFORMACI�N
int MusicRepository::getTotalCanciones() const {
    return numCanciones;
}

bool MusicRepository::estaVacio() const {
    return numCanciones == 0;
}

// M�TODOS PARA POBLAR LISTAS DE LA INTERFAZ
char** MusicRepository::getAllArtists(int& numArtistas) const {
    // Contar artistas �nicos
    numArtistas = 0;
    for (int i = 0; i < numCanciones; i++) {
        std::string artista = canciones[i].getArtist();
        if (!artista.empty()) {
            bool encontrado = false;
            for (int j = 0; j < i; j++) {
                if (canciones[j].getArtist() == artista) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                numArtistas++;
            }
        }
    }

    if (numArtistas == 0) {
        return nullptr;
    }

    // Crear array de strings
    char** artistas = new char*[numArtistas];
    int index = 0;

    for (int i = 0; i < numCanciones; i++) {
        std::string artista = canciones[i].getArtist();
        if (!artista.empty()) {
            bool encontrado = false;
            for (int j = 0; j < i; j++) {
                if (canciones[j].getArtist() == artista) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                artistas[index] = new char[artista.length() + 1];
                strcpy(artistas[index], artista.c_str());
                index++;
            }
        }
    }

    return artistas;
}

char** MusicRepository::getAllAlbums(int& numAlbumes) const {
    numAlbumes = 0;
    for (int i = 0; i < numCanciones; i++) {
        std::string album = canciones[i].getAlbum();
        if (!album.empty()) {
            bool encontrado = false;
            for (int j = 0; j < i; j++) {
                if (canciones[j].getAlbum() == album) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                numAlbumes++;
            }
        }
    }

    if (numAlbumes == 0) {
        return nullptr;
    }

    char** albumes = new char*[numAlbumes];
    int index = 0;

    for (int i = 0; i < numCanciones; i++) {
        std::string album = canciones[i].getAlbum();
        if (!album.empty()) {
            bool encontrado = false;
            for (int j = 0; j < i; j++) {
                if (canciones[j].getAlbum() == album) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                albumes[index] = new char[album.length() + 1];
                strcpy(albumes[index], album.c_str());
                index++;
            }
        }
    }

    return albumes;
}

char** MusicRepository::getAllGenres(int& numGeneros) const {
    numGeneros = 0;
    for (int i = 0; i < numCanciones; i++) {
        std::string genero = canciones[i].getGenre();
        if (!genero.empty()) {
            bool encontrado = false;
            for (int j = 0; j < i; j++) {
                if (canciones[j].getGenre() == genero) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                numGeneros++;
            }
        }
    }

    if (numGeneros == 0) {
        return nullptr;
    }

    char** generos = new char*[numGeneros];
    int index = 0;

    for (int i = 0; i < numCanciones; i++) {
        std::string genero = canciones[i].getGenre();
        if (!genero.empty()) {
            bool encontrado = false;
            for (int j = 0; j < i; j++) {
                if (canciones[j].getGenre() == genero) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                generos[index] = new char[genero.length() + 1];
                strcpy(generos[index], genero.c_str());
                index++;
            }
        }
    }

    return generos;
}

// INFORMACI�N PARA MOSTRAR EN INTERFAZ
std::string MusicRepository::getInfoString() const {
    return "Canciones: " + std::to_string(numCanciones) +
           " | Actual: " + (cancionActual >= 0 ? std::to_string(cancionActual + 1) : "Ninguna");
}

// FUNCIONES PARA LIBERAR MEMORIA
void MusicRepository::liberarArray(int* array) {
    if (array != nullptr) {
        delete[] array;
    }
}

void MusicRepository::liberarArrayStrings(char** array, int tama) {
    if (array != nullptr) {
        for (int i = 0; i < tam; i++) {
            delete[] array[i];
        }
        delete[] array;
    }
}
