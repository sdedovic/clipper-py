import unittest
from clipper_py import *


class GoodEnoughTest(unittest.TestCase):
    def validate_installed_version(self):
        import clipper_py
        self.assertEqual("0.1.5", clipper_py.__version__)

    def test_simple(self):
        subj = Path()
        for x, y in [(10, 10), (90, 10), (90, 90), (10, 90)]:
            subj.append(IntPoint(x, y))

        clip = Path()
        for x, y in [(0, 40), (20, 40), (20, 60), (0, 60)]:
            clip.append(IntPoint(x, y))

        c = Clipper(0)
        c.add_paths(Paths().push(subj), 'subject', True)
        c.add_paths(Paths().push(clip), 'clip', True)

        solution = c.execute("union", 'non-zero', 'non-zero')
        solution = [(point[0], point[1]) for point in solution[0]]

        expected = [(90, 90), (10, 90), (10, 60), (0, 60), (0, 40), (10, 40), (10, 10), (90, 10)]

        self.assertListEqual(solution, expected)

    def test_line(self):
        subj1 = Path()
        for x, y in [(180, 200), (260, 200), (260, 150), (180, 150)]:
            subj1.append(IntPoint(x, y))

        clip = Path()
        for x, y in [(190, 210), (240, 210), (240, 130), (190, 130)]:
            clip.append(IntPoint(x, y))

        print(subj1)
        print(clip)

        c = Clipper(0)
        c.add_paths(Paths().push(subj1), 'subject', False)
        c.add_paths(Paths().push(clip), 'clip', True)

        solution = c.execute_complex("difference", 'non-zero', 'non-zero')

        # open_paths_from_polytree(solution)
        # print(paths)
        # print(closed_paths_from_polytree(solution))
        print(solution.get_open_paths())
