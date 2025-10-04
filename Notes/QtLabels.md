# QtLabels reminder

---

## 🔤 1. **Contenu du texte**

Tu peux afficher :

* du **texte simple** : `label.setText("Mon texte")`
* du **texte enrichi (HTML léger)** : `label.setText("<b>Gras</b> <i>Italique</i>")`

---

## 🎨 2. **Style de police**

```python
from PySide6.QtGui import QFont

# Appliquer une police personnalisée
font = QFont("Arial", 12)         # police Arial, taille 12
font.setBold(True)                # en gras
font.setItalic(True)              # en italique
font.setUnderline(True)           # souligné
label.setFont(font)
```

---

## 📐 3. **Alignement du texte**

```python
from PySide6.QtCore import Qt

label.setAlignment(Qt.AlignCenter)           # Centré (horizontal + vertical)
label.setAlignment(Qt.AlignLeft | Qt.AlignTop)  # Haut-gauche
label.setAlignment(Qt.AlignRight)            # À droite
```

---

## 📏 4. **Marges internes du texte**

```python
label.setContentsMargins(10, 10, 10, 10)  # marges internes : gauche, haut, droite, bas
```

---

## 🧱 5. **Comportement du texte**

```python
label.setWordWrap(True)  # Passe à la ligne automatiquement si trop long
```

---

## 🖼️ 6. **Style CSS (via `setStyleSheet`)**

Tu peux aussi utiliser du **CSS Qt** pour formater tout en une ligne :

```python
label.setStyleSheet("""
    color: #333;
    background-color: #eef;
    font-size: 14px;
    font-weight: bold;
    font-style: italic;
    padding: 10px;
    border: 1px solid #ccc;
""")
```

---

## 📌 Exemple complet

```python
from PySide6.QtWidgets import QLabel, QWidget, QApplication, QVBoxLayout
from PySide6.QtGui import QFont
from PySide6.QtCore import Qt

app = QApplication([])

label = QLabel("Voici du <b>texte</b> <i>formaté</i> dans un QLabel")
label.setAlignment(Qt.AlignCenter)
label.setWordWrap(True)

font = QFont("Verdana", 14)
font.setBold(True)
label.setFont(font)

label.setContentsMargins(20, 10, 20, 10)
label.setStyleSheet("color: darkblue; background-color: #e0f0ff; border: 1px solid gray;")

window = QWidget()
layout = QVBoxLayout(window)
layout.addWidget(label)

window.setWindowTitle("Exemple QLabel formaté")
window.show()
app.exec()
```

---

