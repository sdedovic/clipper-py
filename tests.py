import unittest
from clipper_py import *


class PolyTreeTest(unittest.TestCase):
    def test_polynode(self):
        from clipper_py import PolyNode

        node = PolyNode()

        self.assertEqual("PolyNode(child_count=0 is_open=0 is_hole=1)", str(node))
        self.assertEqual(True, node.is_hole())
        self.assertEqual(False, node.is_open())
        self.assertEqual(None, node.get_next())
        self.assertEqual("PolyNodes( size=0 )", str(node.childs))
        self.assertEqual(None, node.parent)
        self.assertEqual(str(Path()), str(node.contour))
        self.assertEqual(0, node.child_count())

    def test_polytree(self):
        from clipper_py import PolyTree

        tree = PolyTree()

        self.assertEqual("PolyTree(child_count=0 is_open=0 is_hole=1)", str(tree))
        self.assertEqual(True, tree.is_hole())
        self.assertEqual(False, tree.is_open())
        self.assertEqual(None, tree.get_next())
        self.assertEqual("PolyNodes( size=0 )", str(tree.childs))
        self.assertEqual(None, tree.parent)
        self.assertEqual(str(Path()), str(tree.contour))
        self.assertEqual(0, tree.child_count())


class ClipperTest(unittest.TestCase):
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
        for x, y in [(0, 0), (100, 100)]:
            subj1.append(IntPoint(x, y))

        clip = Path()
        for x, y in [(20, 20), (80, 20), (80, 80), (20, 80)]:
            clip.append(IntPoint(x, y))

        c = Clipper(0)
        c.add_paths(Paths().push(subj1), 'subject', False)
        c.add_paths(Paths().push(clip), 'clip', True)

        solution = c.execute_complex("difference", 'non-zero', 'non-zero', 'open')
        solution = [[(point[0], point[1]) for point in paths] for paths in solution]

        self.assertEqual(solution, [[(80, 80), (100, 100)], [(0, 0), (20, 20)]])
