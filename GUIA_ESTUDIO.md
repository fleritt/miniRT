# Guía de Estudio - miniRT Ray Tracer

## 1. Ray Tracing Básico

### ¿Qué es?
Lanzar rayos desde la cámara a través de cada píxel y ver qué objetos intersectan.

### Flujo:
```
Cámara → Rayo por píxel → Intersección → Color → Pantalla
```

### Cálculo de Rayos (hit_sphere.c)
```c
// Para cada píxel (x, y):
px = (2.0 * (x + 0.5) / WIDTH - 1.0) * aspect_ratio * scale
py = (1.0 - 2.0 * (y + 0.5) / HEIGHT) * scale

// Dirección del rayo:
ray_dir = forward + right*px + up*py
```

**Concepto clave**: `scale = tan(FOV/2)` convierte el FOV en distancia del plano de imagen.

---

## 2. Intersecciones

### Esfera (hit_sphere.c)
**Ecuación**: `|P - C|² = r²`

Sustituyendo `P = O + t*D` (rayo):
```c
a = dot(D, D)
b = 2 * dot(O - C, D)
c = dot(O - C, O - C) - r²
discriminante = b² - 4ac

// Si discriminante < 0 → no hay intersección
t = (-b - sqrt(discriminante)) / 2a
```

### Plano (hit_plane.c)
**Ecuación**: `dot(N, P - P₀) = 0`

```c
t = dot(N, P₀ - O) / dot(N, D)
```
Si `dot(N, D) ≈ 0` → rayo paralelo al plano.

---

## 3. Iluminación (Modelo de Phong)

### Fórmula Completa:
```
Color = Ambiente + Difusa + Especular
```

### A) Luz Ambiental (ambient.c)
```c
ambient = color_objeto * intensidad_ambiente * color_luz_ambiente
```
**Concepto**: Luz uniforme que ilumina todo por igual.

### B) Luz Difusa (ambient.c)
```c
L = normalize(luz_pos - punto)  // Vector hacia la luz
diff = max(0, dot(N, L))        // Ángulo de incidencia
diffuse = color_objeto * intensidad_luz * diff * color_luz
```
**Concepto**: Superficies perpendiculares a la luz son más brillantes (Ley de Lambert).

### C) Luz Especular (lighting.c)
```c
R = 2 * dot(N, L) * N - L       // Vector reflejado
V = normalize(camara - punto)    // Vector hacia la vista
spec = pow(max(0, dot(R, V)), shininess)
specular = color_luz * intensidad * spec
```
**Concepto**: Brillo en dirección de reflexión perfecta.
- `shininess` alto → brillo concentrado (metal)
- `shininess` bajo → brillo difuso (plástico)

---

## 4. Sombras (lighting.c)

```c
shadow_ray = {punto + ε*N, dirección_hacia_luz}

for cada_objeto:
    if intersecta(shadow_ray, objeto):
        if distancia < distancia_a_luz:
            → SOMBRA (solo luz ambiental)
```

**Concepto clave**: 
- `ε = 0.001` (offset) evita "acné de sombras"
- Si hay objeto entre punto y luz → no hay luz difusa ni especular

---

## 5. Sistema de Coordenadas de Cámara

```c
forward = normalize(dirección_cámara)
right = normalize(forward × world_up)
up = forward × right
```

**Sistema derecho** (right-handed):
- X (right) → derecha
- Y (up) → arriba  
- Z (forward) → profundidad (hacia donde mira)

---

## 6. Estructura del Renderizado (ft_render.c)

```
for cada_píxel:
    generar_rayo(píxel)
    
    closest_t = infinito
    for cada_objeto:
        if intersecta(rayo, objeto):
            if t < closest_t:
                closest_t = t
                guardar_hit_info
    
    if hit_algo:
        view_dir = normalize(cámara - punto)
        color = calculate_lighting(hit, view_dir)
    
    pintar_píxel(color)
```

**Z-buffering manual**: Guardamos solo el objeto más cercano (`t` más pequeño).

---

## 7. Conceptos Matemáticos Clave

### Producto Punto (dot product)
```c
dot(A, B) = Ax*Bx + Ay*By + Az*Bz = |A||B|cos(θ)
```
**Uso**: Medir ángulos entre vectores (0° = 1, 90° = 0, 180° = -1)

### Producto Cruz (cross product)
```c
A × B = vector perpendicular a A y B
```
**Uso**: Crear sistemas de coordenadas ortogonales.

### Normalización
```c
normalize(V) = V / |V|
```
**Uso**: Vector con misma dirección pero longitud = 1.

---

## 8. Orden de Implementación (lo que hicimos)

1. ✅ Vectores básicos
2. ✅ Ray-sphere intersection
3. ✅ Cámara con FOV
4. ✅ Parser de .rt
5. ✅ Luz ambiental
6. ✅ Luz difusa
7. ✅ Planos
8. ✅ Sombras
9. ✅ Luz especular

---

## 9. Debugging Tips

**Imagen invertida**: Revisar `py` o `camera.up` (producto cruz).

**Esferas muy grandes**: 
- Reducir radio
- Alejar cámara
- Aumentar FOV

**Sombras extrañas**: Ajustar offset `ε` (0.001 → 0.01).

**Sin brillos**: `shininess` muy bajo o `view_dir` mal calculado.

---

## 10. Fórmulas para el Examen 📝

```
1. Intersección esfera:   t = (-b ± √(b²-4ac)) / 2a
2. Intersección plano:    t = dot(N, P₀-O) / dot(N, D)
3. Luz difusa:            I = Kd × max(0, N·L)
4. Luz especular:         I = Ks × (R·V)^n
5. Phong completo:        I = Ka + Kd(N·L) + Ks(R·V)^n
```

---

**Tiempo estimado estudio**: 2-3 horas revisando código + esta guía.

**Archivos clave para revisar**:
- `hit_sphere.c` - Geometría
- `lighting.c` - Iluminación completa  
- `ft_render.c` - Loop principal
- `camera.c` - Sistema de coordenadas
