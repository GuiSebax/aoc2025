using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

class Point
{
    public int X;
    public int Y;
}

class Program
{
    static List<Point> ReadInput(string file)
    {
        return File.ReadAllText(file)
            .Trim()
            .Split(new[] { "\r\n", "\n" }, StringSplitOptions.RemoveEmptyEntries)
            .Select(l =>
            {
                var p = l.Split(',').Select(int.Parse).ToArray();
                return new Point { X = p[0], Y = p[1] };
            })
            .ToList();
    }

    static int Part1(List<Point> points)
    {
        int best = 0;
        for (int i = 0; i < points.Count; i++)
        {
            for (int j = i + 1; j < points.Count; j++)
            {
                int dx = Math.Abs(points[i].X - points[j].X);
                int dy = Math.Abs(points[i].Y - points[j].Y);
                best = Math.Max(best, (dx + 1) * (dy + 1));
            }
        }
        return best;
    }

    static Dictionary<int, List<(int, int)>> BuildInsideIntervals(List<Point> polygon)
    {
        var intervalsByX = new Dictionary<int, List<(int, int)>>();

        int minX = int.MaxValue;
        int maxX = int.MinValue;

        foreach (var p in polygon)
        {
            minX = Math.Min(minX, p.X);
            maxX = Math.Max(maxX, p.X);
        }

        for (int x = minX; x <= maxX; x++)
        {
            var intersections = new List<int>();

            for (int i = 0; i < polygon.Count; i++)
            {
                var a = polygon[i];
                var b = polygon[(i + 1) % polygon.Count];

                if (a.Y == b.Y)
                {
                    int y = a.Y;
                    int x1 = Math.Min(a.X, b.X);
                    int x2 = Math.Max(a.X, b.X);

                    if (x >= x1 && x < x2)
                        intersections.Add(y);
                }
            }

            intersections.Sort();

            var intervals = new List<(int, int)>();
            for (int i = 0; i < intersections.Count; i += 2)
            {
                intervals.Add((intersections[i], intersections[i + 1]));
            }

            if (intervals.Count > 0)
                intervalsByX[x] = intervals;
        }

        return intervalsByX;
    }

    static int Part2(List<Point> points)
    {
        var insideByX = BuildInsideIntervals(points);
        int best = 0;

        for (int i = 0; i < points.Count; i++)
        {
            for (int j = i + 1; j < points.Count; j++)
            {
                var a = points[i];
                var b = points[j];

                if (a.X == b.X || a.Y == b.Y)
                    continue;

                int x1 = Math.Min(a.X, b.X);
                int x2 = Math.Max(a.X, b.X);
                int y1 = Math.Min(a.Y, b.Y);
                int y2 = Math.Max(a.Y, b.Y);

                bool ok = true;

                for (int x = x1; x <= x2; x++)
                {
                    if (!insideByX.TryGetValue(x, out var intervals))
                    {
                        ok = false;
                        break;
                    }

                    bool covered = false;
                    foreach (var (lo, hi) in intervals)
                    {
                        if (lo <= y1 && y2 <= hi)
                        {
                            covered = true;
                            break;
                        }
                    }

                    if (!covered)
                    {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                {
                    int area = (x2 - x1 + 1) * (y2 - y1 + 1);
                    best = Math.Max(best, area);
                }
            }
        }

        return best;
    }

    static void Main()
    {
        var points = ReadInput("input.txt");
        Console.WriteLine("Parte 1: " + Part1(points));
        Console.WriteLine("Parte 2: " + Part2(points));
    }
}
