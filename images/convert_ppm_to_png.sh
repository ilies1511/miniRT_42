#!/bin/bash
mkdir -p images/converted_files
for file in *.ppm; do
  convert "$file" "converted_files/${file%.ppm}.png"
done


# Alternative
# #!/bin/bash

# # Name des Zielordners
# target_dir="converted_files"

# # Überprüfen, ob der Zielordner existiert
# if [ ! -d "$target_dir" ]; then
#   # Ordner erstellen, falls er nicht existiert
#   mkdir "$target_dir"
#   echo "Ordner '$target_dir' wurde erstellt."
# else
#   echo "Ordner '$target_dir' existiert bereits."
# fi

# # Loop durch alle .ppm-Dateien und konvertiere sie
# shopt -s nullglob  # Verhindert, dass die Schleife ausgeführt wird, wenn keine .ppm-Dateien gefunden werden
# for file in *.ppm; do
#   # Überprüfen, ob die Datei existiert
#   if [ -f "$file" ]; then
#     convert "$file" "$target_dir/${file%.ppm}.png"
#     echo "Konvertiere $file zu $target_dir/${file%.ppm}.png"
#   fi
# done

# # Überprüfen, ob keine .ppm-Dateien gefunden wurden
# if [ "$(ls *.ppm 2>/dev/null | wc -l)" -eq 0 ]; then
#   echo "Keine .ppm-Dateien gefunden."
# fi
