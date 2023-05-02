export default function generateSrc(number) {
  if (number < 2 && number >= 0) {
    return `/src/assets/0.svg`;
  } else if (number === 2) {
    return `/src/assets/2.svg`;
  } else if (number == 3) {
    return `/src/assets/3.svg`;
  } else if (number == 45) {
    return `/src/assets/45.svg`;
  } else if (number == 46) {
    return `/src/assets/46.svg`;
  } else if (46 < number <= 51) {
    return `/src/assets/51.svg`;
  } else if (51 < number <= 53) {
    return `/src/assets/53.svg`;
  } else if (53 < number <= 56) {
    return `/src/assets/56.svg`;
  } else if (56 < number <= 61) {
    return `/src/assets/61.svg`;
  } else if (61 < number <= 67) {
    return `/src/assets/67.svg`;
  } else if (67 < number <= 71) {
    return `/src/assets/71.svg`;
  } else if (71 < number) {
    return `/src/assets/80.svg`;
  }
}
