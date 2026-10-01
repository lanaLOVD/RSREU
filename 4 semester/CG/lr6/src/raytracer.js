'use strict';

/* ====================== ВЕКТОРНЫЕ ОПЕРАЦИИ ====================== */
class Vec3 {
  constructor(x, y, z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }

  add(v) {
    return new Vec3(this.x + v.x, this.y + v.y, this.z + v.z);
  }
  sub(v) {
    return new Vec3(this.x - v.x, this.y - v.y, this.z - v.z);
  }
  mul(k) {
    return new Vec3(this.x * k, this.y * k, this.z * k);
  }
  dot(v) {
    return this.x * v.x + this.y * v.y + this.z * v.z;
  }
  length() {
    return Math.sqrt(this.dot(this));
  }

  normalize() {
    const len = this.length();
    return len > 0 ? this.mul(1 / len) : new Vec3(0, 0, 0);
  }

  reflect(N) {
    return this.sub(N.mul(2 * this.dot(N)));
  }
}

/* ====================== СФЕРА ====================== */
class Sphere {
  constructor(center, radius, color, specular, reflective = 0) {
    this.center = center;
    this.radius = radius;
    this.color = color; // {r, g, b}
    this.specular = specular;
    this.reflective = reflective;
  }
}

/* ====================== СЦЕНА ====================== */
const spheres = [
  new Sphere(new Vec3(0, -1, 3), 1, { r: 255, g: 0, b: 0 }, 500, 0.3), // красная
  new Sphere(new Vec3(2, 0, 4), 1, { r: 0, g: 0, b: 255 }, 100, 0.4), // синяя
  new Sphere(new Vec3(-2, 0, 4), 1, { r: 0, g: 255, b: 0 }, 10, 0.2), // зелёная
  new Sphere(new Vec3(0, -5001, 0), 5000, { r: 255, g: 255, b: 100 }, 10, 0.5), // жёлтый пол
];

const lights = [
  { type: 'ambient', intensity: 0.2 },
  { type: 'point', intensity: 0.6, position: new Vec3(2, 1, 0) },
  {
    type: 'directional',
    intensity: 0.2,
    direction: new Vec3(1, 4, 4).normalize(),
  },
];

/* ====================== ПЕРЕСЕЧЕНИЕ ====================== */
function intersectRaySphere(O, D, sphere) {
  const OC = O.sub(sphere.center);
  const k1 = D.dot(D);
  const k2 = 2 * OC.dot(D);
  const k3 = OC.dot(OC) - sphere.radius * sphere.radius;

  const discriminant = k2 * k2 - 4 * k1 * k3;
  if (discriminant < 0) return [Infinity, Infinity];

  const sqrtD = Math.sqrt(discriminant);
  const t1 = (-k2 - sqrtD) / (2 * k1);
  const t2 = (-k2 + sqrtD) / (2 * k1);

  return [t1 > 0 ? t1 : Infinity, t2 > 0 ? t2 : Infinity];
}

function closestIntersection(O, D, t_min, t_max) {
  let closest_t = Infinity;
  let closest_sphere = null;

  for (let sphere of spheres) {
    const ts = intersectRaySphere(O, D, sphere);
    if (ts[0] < closest_t && t_min < ts[0] && ts[0] < t_max) {
      closest_t = ts[0];
      closest_sphere = sphere;
    }
    if (ts[1] < closest_t && t_min < ts[1] && ts[1] < t_max) {
      closest_t = ts[1];
      closest_sphere = sphere;
    }
  }
  return [closest_sphere, closest_t];
}

/* ====================== ОСВЕЩЕНИЕ ====================== */
function computeLighting(P, N, V, specular) {
  let intensity = 0.0;

  for (let light of lights) {
    if (light.type === 'ambient') {
      intensity += light.intensity;
      continue;
    }

    let L = light.type === 'point' ? light.position.sub(P) : light.direction;
    const t_max = light.type === 'point' ? 1.0 : Infinity;

    // Тень
    const shadowResult = closestIntersection(P, L.normalize(), 0.001, t_max);
    if (shadowResult[0] !== null) continue;

    // Diffuse
    const n_dot_l = Math.max(0, N.dot(L));
    intensity += light.intensity * n_dot_l;

    // Specular
    if (specular > 0) {
      const R = L.normalize().reflect(N);
      const r_dot_v = Math.max(0, R.dot(V));
      intensity += light.intensity * Math.pow(r_dot_v, specular);
    }
  }
  return Math.min(intensity, 1.0);
}

/* ====================== ТРАССИРОВКА ====================== */
function traceRay(O, D, t_min, t_max, depth = 0) {
  if (depth > 3) return { r: 0, g: 0, b: 0 };

  const [sphere, t] = closestIntersection(O, D, t_min, t_max);
  if (!sphere) return { r: 0, g: 0, b: 0 };

  const P = O.add(D.mul(t));
  const N = P.sub(sphere.center).normalize();
  const V = D.mul(-1).normalize();

  const lighting = computeLighting(P, N, V, sphere.specular);

  let color = {
    r: Math.floor(sphere.color.r * lighting),
    g: Math.floor(sphere.color.g * lighting),
    b: Math.floor(sphere.color.b * lighting),
  };

  // Отражения
  if (sphere.reflective > 0 && depth < 3) {
    const R = D.reflect(N);
    const reflected = traceRay(P, R.normalize(), 0.001, Infinity, depth + 1);

    color.r = Math.floor(
      color.r * (1 - sphere.reflective) + reflected.r * sphere.reflective,
    );
    color.g = Math.floor(
      color.g * (1 - sphere.reflective) + reflected.g * sphere.reflective,
    );
    color.b = Math.floor(
      color.b * (1 - sphere.reflective) + reflected.b * sphere.reflective,
    );
  }

  return color;
}

/* ====================== РЕНДЕР ====================== */
const canvas = document.getElementById('canvas');
if (canvas) {
  const ctx = canvas.getContext('2d');
  const imageData = ctx.createImageData(800, 600);
  const data = imageData.data;

  const O = new Vec3(0, 0, 0);
  const viewportWidth = 1.6;
  const viewportHeight = 1.2;
  const d = 1;

  let idx = 0;
  for (let py = 299; py >= -300; py--) {
    for (let px = -400; px < 400; px++) {
      const vx = (px / 400) * (viewportWidth / 2);
      const vy = (py / 300) * (viewportHeight / 2);

      const D = new Vec3(vx, vy, d).normalize();
      const color = traceRay(O, D, 1, Infinity);

      data[idx++] = color.r || 0;
      data[idx++] = color.g || 0;
      data[idx++] = color.b || 0;
      data[idx++] = 255;
    }
  }

  ctx.putImageData(imageData, 0, 0);
  console.log(
    '%cРейтрейсинг завершён успешно!',
    'color: lime; font-size: 16px;',
  );
}
