import React from 'react';
import codes from '../data/codes.json';
import generateSrc from '../utilities/generateSrc';
export default function WeatherComponent({ dateTime, data }) {
  return (
    <div className='w-1/4 bg-green-400 rounded-xl flex flex-col'>
      <h3 className='flex-start p-2 rounded-xl bg-green-500 m-2'>{dateTime}</h3>
      <div className='block-content flex flex-row'>
        <img
          className='w-1/4 h-{w-1/4} bg-green-500 m-3 rounded-xl'
          src={`${generateSrc(data.weather_id.id)}`}
        />
        <div className='block-data bg-green-500 w-3/4 m-2 rounded-xl'>
          <ul className='p-1 text-sm'>
            <li>
              {codes.data
                .find((el) => el.code === data.weather_id.id)
                .description.toUpperCase()}
            </li>
            <li>
              {data.min_max_temperature.max +
                ' (' +
                data.min_max_temperature.min +
                ') ' +
                data.min_max_temperature.unit}
            </li>
            <li>
              {'[' +
                data.wind_direction.angle +
                data.wind_direction.unit +
                ']' +
                ' ' +
                data.wind_speed.min +
                ' - ' +
                data.wind_speed.max +
                ' ' +
                data.wind_speed.unit}
            </li>
            <li>{data.visibility.range + ' ' + data.visibility.unit}</li>
            <li>
              {data.precipitation.precipitation_sum.height +
                ' ' +
                data.precipitation.precipitation_sum.unit +
                ' | ' +
                data.precipitation.precipitation_probability.percent +
                ' ' +
                data.precipitation.precipitation_probability.unit}
            </li>
          </ul>
        </div>
      </div>
    </div>
  );
}
