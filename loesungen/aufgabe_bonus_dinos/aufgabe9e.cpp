#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>

#include "camera.hpp"
#include "frame.hpp"
#include "triangle.hpp"
#include "rasterizer.hpp"

// Versucht, eine Zeichenkette in einen numerischen Wert umzuwandeln
//
// \param[in] str
// Die Zeichenkette, die umgewandelt werden soll
//
// \param[out] value
// Eine Referenz auf das Objekt, dass den Wert erhalten soll
//
// \returns
// true, falls die Umwandlung erfolgreich war, sonst false
template<class T_>
bool parse(const char* str, T_& value)
{
  if(str == nullptr)
    return false;

  // Versuche, in tmp einzuelsen
  T_ tmp;
  std::istringstream iss(str);
  if(!(iss >> tmp).fail())
  {
    // Okay
    value = tmp;
    return true;
  }

  // Einlesen gescheitert
  return false;
}

// Funktions-Vorlage:
// Versucht, eine Zeichenkette in einen numerischen Wert umzuwandeln und
// prueft, ob die vorgegebenen Schranken eingehalten werden
//
// Hinweis:
// Bei einem gescheiterten Versuch bleibt 'value' unveraendert.
//
// \param[in] str
// Die Zeichenkette, die umgewandelt werden soll
//
// \param[out] value
// Eine Referenz auf das Objekt, dass den Wert erhalten soll
//
// \param[in] min_value, max_value
// Die Schranken, die value nicht verletzen darf
//
// \returns
// true, falls die Umwandlung erfolgreich war, sonst false
template<class T_>
bool parse(const char* str, T_& value, T_ min_value, T_ max_value)
{
  // Versuche, in tmp einzulesen:
  T_ tmp;
  if(!parse(str, tmp))
    return false;

  // Pruefe, ob die Schranken eingehalten wurden
  if((min_value <= tmp) && (tmp <= max_value))
  {
    // Okay,
    value = tmp;
    return true;
  }

  // Schranken verletzt
  return false;
}

//
// Zeichnet ein Mesh aus einer Datei
//
// \param[in] filename_mesh
// Der Datei-Name der Mesh-Datei.
//
// \param[in,out] frame
// Das Frame, in welches gerendert werden soll
//
// \param[in] camera
// Die Kamera von der aus gerendert werden soll
//
// \returns
// true, falls keine Fehler aufgetreten sind, sonst false
bool render_mesh_file(std::string filename_mesh, Frame& frame, const Camera& camera)
{
  // Versuche, die Eingabe-Datei zu oeffnen und einzulesen:
  std::ifstream ifs(filename_mesh);
  if(!ifs.is_open())
  {
    std::cout << "FEHLER: Konnte '" << filename_mesh << "' nicht oeffnen!" << std::endl;
    return false;
  }

  // Lese Anzahl der Dreiecke
  int num_trias(0);
  if(!(ifs >> num_trias).good())
  {
    std::cout << "FEHLER: Konnte Anzahl der Dreiecke aus '" << filename_mesh << "' nicht einlesen!" << std::endl;
    return false;
  }

  // Stelle sicher, dass die Anzahl nicht verdaechtig gross ist
  if(num_trias > 100000)
  {
    std::cout << "FEHLER: Mehr als 100000 Dreiecke in '" << filename_mesh << "' gefunden!" << std::endl;
    return false;
  }

  // Erstelle Rasterisierer
  Rasterizer raster;

  // Zeiche alle Dreiecke
  for(int i(0); i < num_trias; ++i)
  {
    // Versuche, das Dreieck einzulesen
    Triangle tria;
    if(!(ifs >> tria).good())
    {
      std::cout << "FEHLER: Konnte Dreieck #" << (i+1) << " aus '" << filename_mesh << "' nicht einlesen!" << std::endl;
      return false;
    }

    // Zeichne Dreieck
    raster.render(frame, tria, camera);
  }

  // Okay
  return true;
}

int main(int argc, char** argv)
{
  // Haben einen Datei-Namen?
  if(argc < 2)
  {
    std::cout << argv[0] << " <name> [parameter]" << std::endl;
    return 0;
  }

  // Von der Kommando-Zeile aus einstellbare Parameter:
  int width   =  1280; //  2: Bild-Breite
  int height  =   720; //  3: Bild-Hoehe
  float dist  = 10.0f; //  4: Distanz zur Kamera
  float yaw   =  0.0f; //  5: Gier-Winkel
  float pitch =  0.0f; //  6: Nick-Winkel
  float roll  =  0.0f; //  7: Roll-Winkel
  float c_x   =  0.0f; //  8: Zentrum X
  float c_y   =  0.0f; //  9: Zentrum Y
  float c_z   =  0.0f; // 10: Zentrum Z
  float fovy  =  1.3f; // 11: vertikaler Oeffnungswinkel der Kamera
  float znear =  1.0f; // 12: Nahe Z-Grenze
  float zfar  = 50.0f; // 13: Ferne Z-Grenze

  // Informationen zur Positionierung der Kamera:
  // Die Kamera wird aus Sicht eines Ziel-Punktes ausgerichtet,
  // welcher durch die "Zentrum"-Argumente definiert wird.
  // Das Zentrum liegt i.d.R. im Inneren des Ziel-Objektes.
  //
  // Stellen Sie sich vor, Sie wollen mit Ihrem "Smartphone"
  // ein "Selfie" machen, dann beschreibt das "dist" Argument
  // die Entfernung der Kamera zu Ihnen.
  // Fuer die drei Winkel gilt:
  //
  // 1) Sind alle drei Winkel Null, dann machen Sie ein Foto "von vorne".
  // 2) Der "yaw" Parameter (Gier-Winkel) beschreibt die Drehung
  //    der Kamera um Ihre Hoch-Achse, d.h. "von links" oder "von rechts".
  // 3) Der "pitch" Parameter (Nick-Winkel) beschreibt die Drehung
  //    der Kamera um die Achse, die durch Ihre beiden Schultern verlaeuft,
  //    d.h. "von oben" oder "von unten".
  // 4) Der "roll" Parameter (Roll-Winkel) beschreibt die Drehung
  //    der Kamera um die Achse, die durch Ihren ausgestreckten Arm verlaeuft.
  //
  // Die "fovy", "znear" und "zfar" Parameter sind technische Parameter
  // fuer die Kamera, welche Sie besser nicht veraendern sollten.

  // Generiere Datei-Namen:
  std::string filename_mesh  = std::string("./meshes/") + argv[1] + ".txt";
  std::string filename_color = std::string("./images/") + argv[1] + "-color.jpg";
  std::string filename_depth = std::string("./images/") + argv[1] + "-depth.jpg";

  // Lese Kommando-Zeilen-Argumente ein
  if(argc > 3)
  {
    // Breite und Hoehe
    parse(argv[2],  width, 16, 2048);
    parse(argv[3], height, 16, 2048);
  }
  // Distanz
  if(argc > 4)
    parse(argv[4],  dist,  0.5f, 100.0f);
  // Gier-Winkel
  if(argc > 5)
    parse(argv[5],   yaw, -5.0f,   5.0f);
  // Neige-Winkel
  if(argc > 6)
    parse(argv[6], pitch, -5.0f,   5.0f);
  // Roll-Winkel
  if(argc > 7)
    parse(argv[7],  roll, -5.0f,   5.0f);
  // Zentrum
  if(argc > 10)
  {
    parse(argv[8], c_x);
    parse(argv[9], c_y);
    parse(argv[10], c_z);
  }
  // FOV-Y
  if(argc > 11)
    parse(argv[11], fovy, 0.2f, 2.5f);
  // Z-NEAR/Z-FAR
  if(argc > 13)
  {
    parse(argv[12], znear, 0.01f, 10.0f);
    parse(argv[13], zfar, 1.0f, 1000.0f);
  }

  // Schreibe Parameter auf die Konsole
  std::cout << std::fixed << std::endl;
  std::cout << "Mesh.....: " << filename_mesh << std::endl;
  std::cout << "Breite...: " <<  width << std::endl;
  std::cout << "Hoehe....: " << height << std::endl;
  std::cout << "Distanz..: " <<   dist << std::endl;
  std::cout << "Gier.....: " <<    yaw << std::endl;
  std::cout << "Nick.....: " <<  pitch << std::endl;
  std::cout << "Roll.....: " <<   roll << std::endl;
  std::cout << "Zentrum-X: " <<    c_x << std::endl;
  std::cout << "Zentrum-Y: " <<    c_y << std::endl;
  std::cout << "Zentrum-Z: " <<    c_z << std::endl;
  std::cout << "FOV-Y....: " <<   fovy << std::endl;
  std::cout << "Z-near...: " <<  znear << std::endl;
  std::cout << "Z-far....: " <<   zfar << std::endl;

  // Erstelle Kamera
  Camera camera;
  camera.set_selfie_cam(c_x, c_y, c_z, dist, yaw, pitch, roll);
  camera.set_projection(width, height, fovy, znear, zfar);

  // Erstelle Frame
  Frame frame(width, height);

  // Rendere Mesh aus Datei:
  render_mesh_file(filename_mesh, frame, camera);

  // Schreibe gerenderte Bilder
  frame.write_color_jpeg(filename_color.c_str());
  frame.write_depth_jpeg(filename_depth.c_str());

  // Fertig!
  return 0;
}