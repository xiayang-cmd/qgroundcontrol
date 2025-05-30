import matplotlib.pyplot as plt
import sys
import os


def plot_area(file_path, out_png):
    lines = []
    with open(file_path, 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) == 4:
                x1, y1, x2, y2 = map(float, parts)
                lines.append([(x1, y1), (x2, y2)])
    for seg in lines:
        xs, ys = zip(*seg)
        plt.plot(xs, ys, 'b-')
    plt.title('Area Grid Transects')
    plt.axis('equal')
    plt.savefig(out_png)
    plt.clf()


def plot_corridor(file_path, out_png):
    with open(file_path, 'r') as f:
        for line in f:
            pts = []
            for pair in line.strip().split(','):
                if not pair:
                    continue
                x, y = map(float, pair.split())
                pts.append((x, y))
            xs, ys = zip(*pts)
            plt.plot(xs, ys, 'g-')
    plt.title('Corridor Transects')
    plt.axis('equal')
    plt.savefig(out_png)
    plt.clf()


def main():
    out_dir = sys.argv[1] if len(sys.argv) > 1 else 'output'
    os.makedirs(out_dir, exist_ok=True)
    plot_area(os.path.join(out_dir, 'area_transects.txt'), os.path.join(out_dir, 'area.png'))
    plot_corridor(os.path.join(out_dir, 'corridor_transects.txt'), os.path.join(out_dir, 'corridor.png'))


if __name__ == '__main__':
    main()
