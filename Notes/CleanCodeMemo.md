# Quand utiliser const ?

👉 Quelques règles simples :

1. Toujours mettre **const Type&** pour les paramètres objets que tu ne modifies pas.
(sauf pour les petits types comme int, float → là tu passes par valeur).

1. Mets **const** sur tes méthodes qui ne modifient pas l’objet (Getters, calculs, projections).

1. Mets **const** sur les références de retour si tu ne veux pas que l’extérieur puisse modifier tes données internes.

1. Mets **const** sur les variables locales quand elles ne doivent pas changer (ça aide à comprendre et évite des bugs).

## Exemple :
``` c++
class Collider {
public:
    // Ne modifie pas l’objet : marquée const
    const Vector2D& GetPosition() const { return m_Position; }

    // Modifie l’objet : pas const
    void SetPosition(const Vector2D& pos) { m_Position = pos; }

    // Calcul, pas de modification : const
    virtual void ProjectOntoAxis(const Vector2D& axis, float& min, float& max) const = 0;

protected:
    Vector2D m_Position;
};
```

# Override une méthode virtuelle

Toujours utiliser le mot clé **override** pour éviter les erreurs type faute de frappe.

## Exemple :

```c++
class Collider {
public:
    virtual void Update() = 0;
};

class BoxCollider : public Collider {
public:
    void Updat() override { /* ... */ } // ❌ erreur de compilation, sans override pas d'erreur car le compilo croit que c'est une nouvelle fonction.
};
```



