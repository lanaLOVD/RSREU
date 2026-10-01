import numpy as np
from PIL import Image, ImageDraw
import time
import matplotlib.pyplot as plt

def generate_test_image(size=512):
    img = Image.new('RGB', (size, size), color='white')
    draw = ImageDraw.Draw(img)

    cell = size // 16
    for i in range(16):
        for j in range(16):
            if (i + j) % 2 == 0:
                x0, y0 = i * cell, j * cell
                x1, y1 = x0 + cell, y0 + cell
                draw.rectangle([x0, y0, x1, y1], fill='black')

    draw.line([(0, 0), (size, size // 2)], fill='red', width=3)
    draw.ellipse([size // 4, size // 4, 3 * size // 4, 3 * size // 4], outline='blue', width=4)
    return np.array(img)


def mse(img1, img2):
    return np.mean((img1.astype(np.float32) - img2.astype(np.float32)) ** 2)


def psnr(img1, img2):
    err = mse(img1, img2)
    if err == 0:
        return 100
    return 20 * np.log10(255.0 / np.sqrt(err))


# ===================== SSAA =====================
def ssaa(image, scale=2):
    h, w = image.shape[:2]
    high_h, high_w = h * scale, w * scale
    high_res = np.zeros((high_h, high_w, 3), dtype=np.uint8)

    for hy in range(high_h):
        for hx in range(high_w):
            high_res[hy, hx] = image[hy // scale, hx // scale]

    result = np.zeros((h, w, 3), dtype=np.uint8)

    for y in range(h):
        for x in range(w):
            block = high_res[y * scale:(y + 1) * scale, x * scale:(x + 1) * scale]
            result[y, x] = np.mean(block, axis=(0, 1))

    return result


# ===================== MSAA =====================
def msaa(image, samples=4):
    h, w = image.shape[:2]
    result = np.zeros((h, w, 3), dtype=np.uint8)

    offsets = {
        4: [(-0.25, -0.25), (-0.25, 0.25), (0.25, -0.25), (0.25, 0.25)],
        8: [(-0.375, -0.375), (-0.375, 0), (-0.375, 0.375),
            (0, -0.375), (0, 0.375),
            (0.375, -0.375), (0.375, 0), (0.375, 0.375)]
    }

    off = offsets.get(samples, offsets[4])

    for y in range(h):
        for x in range(w):
            colors = []
            for sy, sx in off:
                ny = int(np.clip(y + sy, 0, h - 1))
                nx = int(np.clip(x + sx, 0, w - 1))
                colors.append(image[ny, nx])
            result[y, x] = np.mean(colors, axis=0)

    return result


# ===================== FXAA =====================
def rgb_to_luma(rgb):
    return 0.299 * rgb[:, :, 0] + 0.587 * rgb[:, :, 1] + 0.114 * rgb[:, :, 2]


def fxaa(image, threshold=0.1):
    h, w = image.shape[:2]
    result = image.copy().astype(np.float32)
    luma = rgb_to_luma(image).astype(np.float32)

    for y in range(1, h - 1):
        for x in range(1, w - 1):
            grad_h = abs(luma[y, x + 1] - luma[y, x - 1])
            grad_v = abs(luma[y + 1, x] - luma[y - 1, x])

            if max(grad_h, grad_v) > threshold:
                if grad_h > grad_v:
                    left = image[y, x - 1]
                    right = image[y, x + 1]
                    result[y, x] = (left + 2 * image[y, x] + right) / 4
                else:
                    up = image[y - 1, x]
                    down = image[y + 1, x]
                    result[y, x] = (up + 2 * image[y, x] + down) / 4

    return result.astype(np.uint8)


# ===================== MAIN =====================
def benchmark(func, image, *args):
    start = time.time()
    output = func(image, *args)
    elapsed = time.time() - start
    quality = psnr(image, output)
    return output, elapsed, quality


def main():
    img = generate_test_image(512)

    results = {}

    results['Original'] = (img, 0, 100)
    results['SSAA 2x'] = benchmark(ssaa, img, 2)
    results['SSAA 4x'] = benchmark(ssaa, img, 4)
    results['MSAA 4x'] = benchmark(msaa, img, 4)
    results['MSAA 8x'] = benchmark(msaa, img, 8)
    results['FXAA'] = benchmark(fxaa, img)

    print('=' * 70)
    print('{:<12} {:<15} {:<15}'.format('Method', 'Time (sec)', 'PSNR'))
    print('=' * 70)

    for name, (_, t, q) in results.items():
        print('{:<12} {:<15.4f} {:<15.2f}'.format(name, t, q))

    fig, axes = plt.subplots(2, 3, figsize=(14, 9))
    axes = axes.flatten()

    for ax, (name, (image, t, q)) in zip(axes, results.items()):
        ax.imshow(image)
        ax.set_title(f'{name}\n{t:.3f}s | PSNR={q:.1f}')
        ax.axis('off')

    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    main()
