
import pyautogui
import sys
import time

def get_position(sqr):
    left, right, up, down = 57, 488, 425, 857
    #left, right, up, down = 100, 424, 454, 778
    row, col = sqr // 4, sqr % 4
    xdist, ydist = (right - left) / 4, (down - up) / 4
    resx, resy = (left + (col + 0.5) * xdist), (up + (row + 0.5) * ydist)
    return (resx, resy)

def main():
    pyautogui.PAUSE = 0.02
    for line in sys.stdin.readlines():
        path = map(int, line.split())
        pyautogui.moveTo(get_position(next(path)))
        pyautogui.mouseDown()
        for sqr in path:
            pyautogui.moveTo(get_position(sqr))
        pyautogui.mouseUp()

if __name__ == "__main__":
    main()
