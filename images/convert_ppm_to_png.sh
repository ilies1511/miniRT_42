# #!/bin/bash
# mkdir -p images/converted_files
# for file in *.ppm; do
#   magick "$file" "converted_files/${file%.ppm}.png"
# done

source_dir="images"
target_dir="converted_files"

# Überprüfen, ob die .ppm-Dateien im aktuellen Verzeichnis vorhanden sind
shopt -s nullglob
ppm_files=($source_dir/*.ppm)

# Wenn keine .ppm-Dateien gefunden werden, breche das Skript ab
if [ ${#ppm_files[@]} -eq 0 ]; then
  echo "Keine .ppm-Dateien im Ordner $source_dir gefunden."
  exit 1
fi

# Zielordner erstellen, falls er nicht existiert
mkdir -p "$source_dir/$target_dir"

# Schleife zum Konvertieren jeder .ppm-Datei
for file in $source_dir/*.ppm; do
  if [ -f "$file" ]; then
    filename=$(basename "$file")  # Extrahiere den Dateinamen
    magick "$file" "$source_dir/$target_dir/${filename%.ppm}.png"
    echo "Konvertiere $file nach $source_dir/$target_dir/${filename%.ppm}.png"
  fi
done

echo "Konvertierung abgeschlossen."

