// AUTOR: Rodrigo Garcia Jimenez
// FECHA: 26-05-2020
// EMAIL: alu0101154473@ull.edu.es 
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 6
// COMENTARIOS: se indican entre [] las pautas de estilo aplicadas de
//              "C++ Programming Style Guidelines"
//              https://geosoft.no/development/cppstyle.html

#include "maze_t.hpp"

/// constructor
maze_t::maze_t():
matrix_(),
visited_(), 
i_start_(-1),
j_start_(-1), 
i_end_(-1),
j_end_(-1)
{}

/// destructor
maze_t::~maze_t()
{}

/// método que resuelve el laberinto invocando al método recursivo
bool maze_t::solve() {
  return solve_(i_start_, j_start_);
}

/// lee el laberinto en forma de matriz desde la entrada
istream& maze_t::read(istream& is) { 
  int m, n;
  is >> m >> n;
  assert(m > 0 && n > 0);
  
  matrix_.resize(m, n);
  visited_.resize(m, n);
  
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      short s;
      is >> s;
      
      /// si el dato es un START_ID -> entrada al laberinto
      if (s == START_ID) {
        i_start_ = i;
        j_start_ = j;
      } else if (s == END_ID) { /// si el dato es un END_ID -> salida al laberinto
        i_end_ = i;
        j_end_   = j;
      }
      matrix_(i, j) = s;
    }
  }
  /// comprobamos que se han leído correctamente la entrada y la salida
  assert (i_start_ != -1 && j_start_ != -1 && i_end_ != -1 && j_end_ != -1);
  FillHeuristica(); /// una vez comprobado que hay llegada y salida, llenamos heurística
  return is;
}

/// Llena la matriz_t heurística
void maze_t::FillHeuristica() {
  heuristica_.resize(matrix_.get_m(), matrix_.get_n());

  for (int i = 1; i <= heuristica_.get_m(); i++) {
    for (int j = 1; j <= heuristica_.get_n(); j++) {
      if (is_ok_(i,j)) { 
        heuristica_(i,j) = fabs((i - i_end_) + (j - j_end_));;
      } else {
        heuristica_(i,j) = NULL;
      }
    }
  }
}

/// muestra el laberinto por pantalla
ostream& maze_t::write(ostream& os) const {
  os << matrix_.get_m() << "x" << matrix_.get_n() << endl;
  for (int i = 1; i <= matrix_.get_m(); i++) {
    for (int j = 1; j <= matrix_.get_n(); j++) {
      switch (matrix_(i, j)) { 
        case START_ID: 
          os << START_CHR; 
          break;
        case END_ID:   
          os << END_CHR;   
          break;
        case WALL_ID:  
          os << WALL_CHR;  
          break;
        case PASS_ID:  
          os << PASS_CHR;  
          break;
        case PATH_ID:  
          os << PATH_CHR;  
          break;
      }
    os << endl;
    }
  }
  return os; 
}

/// Te devuelve el cálculo de la euclídea en el caso i j
float maze_t::Euclidea(const int i, const int j) {
  return sqrt(pow((i - i_end_), 2) + pow((j - j_end_), 2));
}

/// Genera un Maze random pasándole el i j tanto del inicio como del final y
/// el porcentaje de obstaculos requerido 
void maze_t::RandomMaze(const int i_start, const int j_start, const int i_end, const int j_end, const float percentage) {
  const int maze_size = (matrix_.get_n() * matrix_.get_m())
  
  for (int i = 0; i < ; i++) {
    
  }
}

/// Comprueba que la fila i y columna j son válidas antes de pasar a ellas
bool maze_t::is_ok_(const int i, const int j) const { 
  if ((i > 1 && i <= matrix_.get_m()) && (j > 1 && j <= matrix_.get_n()) && (matrix_(i,j) != WALL_ID) && (visited_(i,j) == false)) {
	  return true;
  } else { 
	  return false;
  }
}

/// FASE II y FASE III
/// método recursivo que resuelve el laberinto
bool maze_t::solve_(const int i, const int j) {
  int heuristica_N, heuristica_E, heuristica_S, heuristica_W, menor_heuristica;
  /// CASO BASE:
  if (matrix_(i,j) == END_ID) {
	  cout << "Numero de veces que se retrocede: " << count << endl; // modificacion 
  	return true;
  }
  visited_(i, j) = true;

  /// CASO GENERAL:
  heuristica_N = heuristica_(i + i_d[1], j + i_d[1]); /// matriz
  heuristica_E = heuristica_(i + i_d[2], j + i_d[2]); 
  heuristica_S = heuristica_(i + i_d[3], j + i_d[3]);
  heuristica_W = heuristica_(i + i_d[4], j + i_d[4]);

  menor_heuristica = min(min(heuristica_N, heuristica_E), min(heuristica_S, heuristica_W)); 

  for(int k = 0; k < 4; k++) {
    if (menor_heuristica == heuristica_(i + i_d[k], j + j_d[k])) {
		  if (is_ok_(i + i_d[k], j + j_d[k])) {
			  if (solve_(i + i_d[k], j + j_d[k])) {
				  matrix_(i + i_d[k], j + j_d[k]) = PATH_ID;
				  return true;
			  }
		  }
    }
 	}
  visited_(i, j) = false;
	count++;		/// modificacion
  return false;
}

/// operador de entrada sobrecargado
istream& operator>>(istream& is, maze_t& M) {
  return M.read(is);
}

/// operador de salida sobrecargado
ostream& operator<<(ostream& os, const maze_t& M) {
  return M.write(os);
}