#ifndef MUSICREPOSITORY_H
#define MUSICREPOSITORY_H
//para saber si no hay datos repetidos o datos que no esten definidos, si no esta definido lo define y sigue y si esta definido sigue


#include "Song.h"
#include <string
//usted ya sabe para que es asi que aja (tomas), no te puedo decir todo



class MusicRepository {
private:
    Song* canciones;
    int capacidad;
    int numCanciones;
    int cancionActual;
    std::string libraryPath;

    void redimensionar(int nuevaCapacidad);

public:
    // Constructores y destructor
    MusicRepository();
    MusicRepository(const MusicRepository& otro); //esto funciona para copiar ek repositorio, sirve para crear playlist a partir de otra sin modificar
    MusicRepository& operator=(const MusicRepository& otro); //funciona para crear una play lsit a partir de otra (para agregar canciones en la lista actual temporal)
    ~MusicRepository(); //borrar

    // Gestión de biblioteca
    void setLibraryPath(const std::string& path);
    std::string getLibraryPath() const;  //El setter y getter para buscar las canciones
    bool scanDirectory(const std::string& directory = ""); //Busca las cacniones
    void agregarCancion(const Song& cancion);
    bool eliminarCancion(int index);
    void limpiarRepository();

    // Búsqueda y acceso
    Song* obtenerCancion(int index);
    const Song* obtenerCancion(int index) const;

    // Búsquedas para la interfaz
    int* buscarPorTitulo(const std::string& titulo, int& numResultados) const;
    int* buscarPorArtista(const std::string& artista, int& numResultados) const;
    int* buscarPorAlbum(const std::string& album, int& numResultados) const;
    int* buscarTexto(const std::string& texto, int& numResultados) const;

    // Navegación
    Song* getCurrentSong();
    int getNextIndex();
    int getPreviousIndex();
    void setCurrentIndex(int index);
    int getCurrentIndex() const;

    // Información para la interfaz
    int getTotalCanciones() const;
    bool estaVacio() const;

    // Métodos para poblar listas de la interfaz
    char** getAllArtists(int& numArtistas) const;
    char** getAllAlbums(int& numAlbumes) const;
    char** getAllGenres(int& numGeneros) const;

    // Utilidades para la interfaz
    std::string getInfoString() const;

    // Liberar memoria de arrays devueltos
    static void liberarArray(int* array);
    static void liberarArrayStrings(char** array, int tamaño);

};

#endif
