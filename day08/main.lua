local function trim(s)
    return s:match("^%s*(.-)%s*$")
end

local function parseArgs(argv)
    local args = { part = 1, k = 1000, file = nil }

    if argv[1] and not argv[1]:match("^%-%-") then
        args.file = argv[1]
    end

    for _, a in ipairs(argv) do
        if a:match("^%-%-part=") then
            args.part = tonumber(a:match("=(.+)")) or 1
        elseif a:match("^%-%-k=") then
            args.k = tonumber(a:match("=(.+)")) or 1000
        end
    end

    if args.part ~= 1 and args.part ~= 2 then args.part = 1 end
    if not args.k or args.k < 0 then args.k = 1000 end

    return args
end

local function readInput(file)
    local lines = {}

    if file then
        for line in io.lines(file) do
            table.insert(lines, trim(line))
        end
    else
        for line in io.lines() do
            table.insert(lines, trim(line))
        end
    end

    local pts = {}
    for i, ln in ipairs(lines) do
        if ln ~= "" then
            local x, y, z = ln:match("([^,]+),([^,]+),([^,]+)")
            x, y, z = tonumber(x), tonumber(y), tonumber(z)
            if not (x and y and z) then
                error("Linha inválida (" .. i .. "): " .. ln)
            end
            table.insert(pts, { x = x, y = y, z = z })
        end
    end

    return pts
end

local DSU = {}
DSU.__index = DSU

function DSU.new(n)
    local self = setmetatable({}, DSU)
    self.parent = {}
    self.size = {}
    self.components = n

    for i = 1, n do
        self.parent[i] = i
        self.size[i] = 1
    end

    return self
end

function DSU:find(a)
    if self.parent[a] ~= a then
        self.parent[a] = self:find(self.parent[a])
    end
    return self.parent[a]
end

function DSU:union(a, b)
    local ra = self:find(a)
    local rb = self:find(b)

    if ra == rb then return false end

    if self.size[ra] < self.size[rb] then
        ra, rb = rb, ra
    end

    self.parent[rb] = ra
    self.size[ra] = self.size[ra] + self.size[rb]
    self.components = self.components - 1
    return true
end

function DSU:compSizes()
    local seen = {}
    for i = 1, #self.parent do
        local r = self:find(i)
        seen[r] = (seen[r] or 0) + 1
    end

    local sizes = {}
    for _, v in pairs(seen) do
        table.insert(sizes, v)
    end
    return sizes
end

local function dist2(p, q)
    local dx = p.x - q.x
    local dy = p.y - q.y
    local dz = p.z - q.z
    return dx * dx + dy * dy + dz * dz
end

local function buildAllEdgesSorted(points)
    local edges = {}
    local n = #points

    for i = 1, n do
        for j = i + 1, n do
            table.insert(edges, {
                dist2(points[i], points[j]),
                i,
                j
            })
        end
    end

    table.sort(edges, function(a, b)
        if a[1] ~= b[1] then return a[1] < b[1] end
        if a[2] ~= b[2] then return a[2] < b[2] end
        return a[3] < b[3]
    end)

    return edges
end

local function part1(points, k)
    local n = #points
    local edges = buildAllEdgesSorted(points)
    local dsu = DSU.new(n)

    local limit = math.min(k, #edges)
    for i = 1, limit do
        local _, a, b = table.unpack(edges[i])
        dsu:union(a, b)
    end

    local sizes = dsu:compSizes()
    table.sort(sizes, function(a, b) return a > b end)

    local a = sizes[1] or 1
    local b = sizes[2] or 1
    local c = sizes[3] or 1

    return a * b * c
end

local function part2(points)
    local n = #points
    local edges = buildAllEdgesSorted(points)
    local dsu = DSU.new(n)

    local lastI, lastJ = nil, nil

    for _, e in ipairs(edges) do
        local _, i, j = table.unpack(e)
        if dsu:union(i, j) then
            lastI, lastJ = i, j
            if dsu.components == 1 then break end
        end
    end

    if not lastI then return 0 end
    return points[lastI].x * points[lastJ].x
end

local args = parseArgs(arg)
local points = readInput(args.file)

if args.part == 1 then
    print(part1(points, args.k))
else
    print(part2(points))
end
