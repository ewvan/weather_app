import axios from 'axios';
import json from '/src/config.json';
export default async function fetchData() {
  try {
    const { cities } = json;
    const data = await axios
      .get(
        'http://localhost:8080/0.0.0.0:80/cities' +
          cities.reduce((prev, curr, index) => {
            return (prev += `${index === 0 ? '?' : '&'}city${index}=${curr}`);
          }, '')
      )
      .then((response) => response.data.data);

    return data;
  } catch (error) {
    throw new Error(error);
  }
}
