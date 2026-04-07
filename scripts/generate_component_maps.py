from pathlib import Path

from PIL import Image, ImageDraw, ImageFont


ROOT = Path(__file__).resolve().parents[1]
OUT_DIR = ROOT / "figures"
OUT_DIR.mkdir(exist_ok=True)

W, H = 1600, 900
BG = (247, 250, 252)
OUTLINE = (44, 52, 64)
BODY = (114, 125, 106)
BODY_DARK = (82, 91, 78)
WINDOW = (60, 82, 110)
SHADOW = (190, 198, 202)
CALLOUT_BG = (255, 255, 255)
CALLOUT_BORDER = (52, 73, 94)


def load_font(size: int, bold: bool = False):
    candidates = []
    if bold:
        candidates.extend(
            [
                r"C:\Windows\Fonts\arialbd.ttf",
                r"C:\Windows\Fonts\segoeuib.ttf",
            ]
        )
    candidates.extend(
        [
            r"C:\Windows\Fonts\arial.ttf",
            r"C:\Windows\Fonts\segoeui.ttf",
            r"C:\Windows\Fonts\calibri.ttf",
        ]
    )
    for candidate in candidates:
        path = Path(candidate)
        if path.exists():
            return ImageFont.truetype(str(path), size=size)
    return ImageFont.load_default()


TITLE_FONT = load_font(42, bold=True)
LABEL_FONT = load_font(26, bold=True)
TEXT_FONT = load_font(22)


def line(draw, pts, fill, width):
    draw.line(pts, fill=fill, width=width, joint="curve")


def draw_base(draw: ImageDraw.ImageDraw):
    draw.rectangle((0, 0, W, H), fill=BG)

    # Ground shadow
    draw.ellipse((150, 710, 1130, 845), fill=SHADOW)

    # Main fuselage / cabin
    cabin = [
        (165, 575),
        (190, 465),
        (275, 410),
        (450, 375),
        (685, 360),
        (785, 385),
        (820, 465),
        (790, 555),
        (670, 595),
        (325, 615),
        (210, 610),
    ]
    draw.polygon(cabin, fill=BODY, outline=OUTLINE)

    # Nose glazing
    draw.polygon(
        [(185, 545), (250, 430), (330, 410), (330, 550), (245, 570)],
        fill=WINDOW,
        outline=OUTLINE,
    )

    # Doors and windows
    for box in [
        (355, 430, 430, 565),
        (448, 430, 590, 570),
        (610, 430, 760, 555),
    ]:
        draw.rounded_rectangle(box, radius=10, fill=(75, 78, 82), outline=OUTLINE, width=3)

    # Roof / engine doghouse
    doghouse = [
        (420, 330),
        (470, 280),
        (670, 265),
        (810, 275),
        (855, 330),
        (845, 400),
        (430, 400),
    ]
    draw.polygon(doghouse, fill=BODY_DARK, outline=OUTLINE)
    draw.rounded_rectangle((520, 310, 570, 380), radius=8, fill=(55, 56, 58), outline=OUTLINE, width=3)
    for box in [(620, 312, 680, 372), (690, 312, 748, 370)]:
        draw.rounded_rectangle(box, radius=8, fill=(106, 108, 97), outline=OUTLINE, width=3)

    # Tail boom
    boom = [
        (785, 408),
        (1125, 360),
        (1338, 312),
        (1380, 290),
        (1397, 314),
        (1348, 350),
        (1138, 400),
        (810, 442),
    ]
    draw.polygon(boom, fill=BODY, outline=OUTLINE)

    # Fin
    fin = [(1320, 300), (1452, 168), (1483, 177), (1402, 325), (1355, 360)]
    draw.polygon(fin, fill=BODY_DARK, outline=OUTLINE)

    # Horizontal stabilizer
    stab = [(1205, 436), (1334, 414), (1365, 430), (1238, 456)]
    draw.polygon(stab, fill=(124, 132, 86), outline=OUTLINE)

    # Tail rotor
    line(draw, [(1452, 180), (1550, 177)], OUTLINE, 14)
    line(draw, [(1500, 135), (1490, 222)], OUTLINE, 10)
    draw.ellipse((1479, 163, 1512, 196), fill=(78, 84, 72), outline=OUTLINE)

    # Mast / hub / head
    draw.rectangle((520, 220, 545, 360), fill=(78, 84, 72), outline=OUTLINE)
    draw.rounded_rectangle((500, 245, 585, 285), radius=8, fill=(72, 77, 70), outline=OUTLINE, width=3)
    draw.rectangle((485, 286, 605, 302), fill=(62, 67, 60), outline=OUTLINE)
    line(draw, [(530, 220), (440, 208)], OUTLINE, 8)
    line(draw, [(534, 220), (1505, 305)], OUTLINE, 10)
    line(draw, [(528, 220), (24, 235)], OUTLINE, 10)

    # Skids
    line(draw, [(325, 602), (305, 700)], OUTLINE, 8)
    line(draw, [(650, 585), (660, 700)], OUTLINE, 8)
    line(draw, [(282, 705), (700, 705)], OUTLINE, 9)
    line(draw, [(300, 705), (245, 750), (415, 750), (365, 705)], OUTLINE, 6)
    line(draw, [(620, 705), (758, 705)], OUTLINE, 8)

    # Ground
    line(draw, [(70, 788), (1530, 788)], (101, 110, 120), 4)


def callout(draw, box, target, title, detail, color):
    x1, y1, x2, y2 = box
    draw.rounded_rectangle(box, radius=18, fill=CALLOUT_BG, outline=color, width=4)
    text_x = x1 + 18
    draw.text((text_x, y1 + 14), title, fill=color, font=LABEL_FONT)
    draw.text((text_x, y1 + 52), detail, fill=CALLOUT_BORDER, font=TEXT_FONT)

    anchor = (x1, (y1 + y2) // 2) if target[0] < x1 else (x2, (y1 + y2) // 2)
    line(draw, [anchor, target], color, 5)
    draw.ellipse((target[0] - 8, target[1] - 8, target[0] + 8, target[1] + 8), fill=color)


def title_block(draw, title, subtitle, color):
    draw.rounded_rectangle((46, 36, 910, 132), radius=22, fill=(255, 255, 255), outline=color, width=4)
    draw.text((72, 52), title, fill=color, font=TITLE_FONT)
    draw.text((74, 98), subtitle, fill=CALLOUT_BORDER, font=TEXT_FONT)


def export_map(filename, title, subtitle, highlights):
    image = Image.new("RGB", (W, H), BG)
    draw = ImageDraw.Draw(image)
    draw_base(draw)
    title_block(draw, title, subtitle, highlights[0]["color"])

    for item in highlights:
        if "shape" in item:
            item["shape"](draw, item["color"])
        callout(draw, item["box"], item["target"], item["title"], item["detail"], item["color"])

    image.save(OUT_DIR / filename)


def rotor_disk_shape(draw, color):
    draw.ellipse((80, 140, 1520, 360), outline=color, width=6)
    draw.ellipse((505, 235, 565, 295), fill=color, outline=OUTLINE)


def engine_shape(draw, color):
    draw.rounded_rectangle((430, 258, 855, 405), radius=20, outline=color, width=6)


def cabin_shape(draw, color):
    draw.rounded_rectangle((150, 360, 815, 618), radius=28, outline=color, width=6)


def tail_boom_shape(draw, color):
    draw.polygon(
        [(780, 400), (1128, 350), (1384, 296), (1400, 322), (1140, 402), (806, 445)],
        outline=color,
        width=6,
    )


def skid_shape(draw, color):
    draw.rounded_rectangle((240, 585, 770, 760), radius=26, outline=color, width=6)


def tail_shape(draw, color):
    draw.rounded_rectangle((1190, 150, 1565, 470), radius=26, outline=color, width=6)


def ground_shape(draw, color):
    draw.rectangle((60, 772, 1540, 806), outline=color, width=5)


export_map(
    "uh1_component_map_1_rotor_system.png",
    "UH-1 Component Map 1",
    "Rotor-system model placement: blade, rotor disk, hub, engine/transmission zone",
    [
        {
            "title": "Blade model",
            "detail": "Elemental lift/drag along the main blade span",
            "box": (1080, 72, 1540, 170),
            "target": (1260, 287),
            "color": (220, 50, 47),
            "shape": rotor_disk_shape,
        },
        {
            "title": "Rotor model",
            "detail": "Integrated main-rotor thrust and induced torque",
            "box": (1030, 230, 1540, 328),
            "target": (808, 260),
            "color": (38, 139, 210),
        },
        {
            "title": "Hub model",
            "detail": "Hub drag, mast loads, and load transfer point",
            "box": (1020, 388, 1540, 486),
            "target": (535, 276),
            "color": (203, 75, 22),
        },
        {
            "title": "Engine model",
            "detail": "Power source and drivetrain coupling to the rotor",
            "box": (64, 680, 620, 778),
            "target": (675, 332),
            "color": (42, 161, 152),
            "shape": engine_shape,
        },
    ],
)

export_map(
    "uh1_component_map_2_fuselage_system.png",
    "UH-1 Component Map 2",
    "Airframe model placement: cabin, tail boom, and landing skid",
    [
        {
            "title": "Cabin model",
            "detail": "Forebody drag, side force, download, and roof interference",
            "box": (950, 92, 1540, 190),
            "target": (425, 492),
            "color": (211, 54, 130),
            "shape": cabin_shape,
        },
        {
            "title": "Tail boom model",
            "detail": "Aft-fuselage drag plus main-rotor wake impingement",
            "box": (940, 252, 1540, 350),
            "target": (1060, 380),
            "color": (133, 153, 0),
            "shape": tail_boom_shape,
        },
        {
            "title": "Skid model",
            "detail": "Flight drag and landing-load transmission path",
            "box": (60, 150, 640, 248),
            "target": (470, 708),
            "color": (181, 137, 0),
            "shape": skid_shape,
        },
    ],
)

export_map(
    "uh1_component_map_3_tail_ground_system.png",
    "UH-1 Component Map 3",
    "Tail and environment model placement: fin, stabilizer, tail rotor, ground",
    [
        {
            "title": "Fin model",
            "detail": "Vertical tail side-force and yaw-stability surface",
            "box": (60, 150, 620, 248),
            "target": (1394, 268),
            "color": (108, 113, 196),
            "shape": tail_shape,
        },
        {
            "title": "Horizontal stabilizer model",
            "detail": "Tailplane lift/downforce and pitch-trim relief",
            "box": (60, 270, 720, 368),
            "target": (1275, 434),
            "color": (46, 204, 113),
        },
        {
            "title": "Tail rotor model",
            "detail": "Anti-torque side force and tail-rotor moment arm",
            "box": (66, 390, 680, 488),
            "target": (1498, 180),
            "color": (231, 76, 60),
        },
        {
            "title": "Ground model",
            "detail": "Ground-effect boundary and skid reaction reference plane",
            "box": (936, 676, 1540, 774),
            "target": (1010, 788),
            "color": (52, 152, 219),
            "shape": ground_shape,
        },
    ],
)

print("Generated:")
for name in [
    "uh1_component_map_1_rotor_system.png",
    "uh1_component_map_2_fuselage_system.png",
    "uh1_component_map_3_tail_ground_system.png",
]:
    print(OUT_DIR / name)
