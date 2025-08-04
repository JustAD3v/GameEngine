# tilemap_saver.py
import xml.etree.ElementTree as ET

def save_tilemap(scene, filename):
    root = ET.Element("tilemap")
    for item in scene.items():
        if hasattr(item, "pixmap"):  # vérifier si c'est une tuile
            x, y = int(item.pos().x()), int(item.pos().y())
            tile = ET.SubElement(root, "tile")
            tile.set("x", str(x))
            tile.set("y", str(y))
            # Ici, on pourrait stocker un ID ou couleur, etc.

    tree = ET.ElementTree(root)
    tree.write(filename)
