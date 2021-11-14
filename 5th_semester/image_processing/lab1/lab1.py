#  Lab1: Draw line, circle and ellipse on bitmap image
#  Here i used Bresenham's line algorithm
import streamlit as st
import numpy as np

WIDTH = 800
HEIGHT = 600

def draw_line(x1: int, y1: int, x2: int, y2: int) -> np.ndarray:
    image = np.ones(shape=(HEIGHT, WIDTH))

    dx = np.abs(x2 - x1)
    sx = 1 if x1 < x2 else -1
    dy = -np.abs(y2 - y1)
    sy = 1 if y1 < y2 else -1
    err = dx + dy
    while True:
        image[HEIGHT - y1][x1] = 0
        if x1 == x2 and y1 == y2:
            break
        e2 = 2 * err
        if e2 >= dy:
            err += dy
            x1 += sx
        if e2 <= dx:
            err += dx
            y1 += sy

    return image


def plot_ellipse_points(x: int, y: int, cx: int, cy: int, image: np.ndarray) -> np.ndarray:
    if 0 < cx + x < WIDTH and HEIGHT - cy - y >= 0 and cy + y > 0:
        image[HEIGHT - cy - y][cx + x] = 0
    if 0 < cx - x < WIDTH and HEIGHT - cy - y >= 0 and cy + y > 0:
        image[HEIGHT - cy - y][cx - x] = 0
    if 0 < cx + x < WIDTH and HEIGHT - cy + y >= 0 and cy - y > 0:
        image[HEIGHT - cy + y][cx + x] = 0
    if 0 < cx - x < WIDTH and HEIGHT - cy + y >= 0 and cy - y > 0:
        image[HEIGHT - cy + y][cx - x] = 0

    return image


def draw_ellipse(x0: int, y0: int, rx: int, ry: int) -> np.ndarray:
    image = np.ones(shape=(HEIGHT, WIDTH))
    a = 2 * (rx ** 2)
    b = 2 * (ry ** 2)
    x = rx
    y = 0
    dx = (1 - 2 * rx) * (ry ** 2)
    dy = rx ** 2
    error = 0
    stop_x = b * rx
    stop_y = 0

    while stop_x >= stop_y:
        image = plot_ellipse_points(x=x, y=y, cx=x0, cy=y0, image=image)
        y += 1
        stop_y += a
        error += dy
        dy += a
        if 2 * error + dx > 0:
            x -= 1
            stop_x -= b
            error += dx
            dx += b

    x = 0
    y = ry
    dx = ry ** 2
    dy = (1 - 2 * ry) * (rx ** 2)
    error = 0
    stop_x = 0
    stop_y = a * ry
    while stop_x <= stop_y:
        image = plot_ellipse_points(x=x, y=y, cx=x0, cy=y0, image=image)
        x += 1
        stop_x += b
        error += dx
        dx += b
        if 2 * error + dy > 0:
            y -= 1
            stop_y -= a
            error += dy
            dy += a

    return image


def run_app():
    shape = st.sidebar.selectbox(label="Object", options=("Line", "Circle", "Ellipse"))
    if shape == "Line":
        x1 = st.sidebar.number_input("Start X", min_value=0, max_value=WIDTH - 1, step=1)
        y1 = st.sidebar.number_input("Start Y", min_value=0, max_value=HEIGHT - 1, step=1)
        x2 = st.sidebar.number_input("End X", min_value=0, max_value=WIDTH - 1, step=1)
        y2 = st.sidebar.number_input("End Y", min_value=0, max_value=HEIGHT - 1, step=1)
        run = st.sidebar.button(label="Run")
        if run:
            result_image = draw_line(x1, y1, x2, y2)
            st.image(result_image)
    elif shape == "Circle":
        x0 = st.sidebar.number_input("Center X", min_value=0, max_value=WIDTH, step=1)
        y0 = st.sidebar.number_input("Center Y", min_value=0, max_value=HEIGHT, step=1)
        radius = st.sidebar.number_input("Radius", min_value=0,
                                         max_value=HEIGHT // 2 if HEIGHT < WIDTH else WIDTH // 2, step=1)
        run = st.sidebar.button(label="Run")
        if run:
            result_image = draw_ellipse(x0, y0, radius, radius)
            st.image(result_image)
    elif shape == "Ellipse":
        x0 = st.sidebar.number_input("Center X", min_value=0, max_value=WIDTH, step=1)
        y0 = st.sidebar.number_input("Center Y", min_value=0, max_value=HEIGHT, step=1)
        x_radius = st.sidebar.number_input("Horizontal radius", min_value=0, max_value=WIDTH // 2, step=1)
        y_radius = st.sidebar.number_input("Vertical radius", min_value=0, max_value=HEIGHT // 2, step=1)
        run = st.sidebar.button(label="Run")
        if run:
            result_image = draw_ellipse(x0, y0, x_radius, y_radius)
            st.image(result_image)


if __name__ == '__main__':
    run_app()
